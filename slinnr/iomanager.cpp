#include "iomanager.h"
#include "log.h"

#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <string>
#include <errno.h>

namespace sylar{

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");


IOManager::FdContext::EventContext& IOManager::FdContext::getContext(IOManager::Event event){
    switch (event)
    {
    case IOManager::READ:
        return read;
    case IOManager::WRITE:
        return write;    
    default:
        SYLAR_ASSERT2(false, "getContext");
    }
}

void IOManager::FdContext::resetContext(EventContext& ctx){
    ctx.scheduler = nullptr;
    ctx.fiber.reset();
    ctx.cb = nullptr;
}

void IOManager::FdContext::triggerEvent(IOManager::Event event){
    SYLAR_ASSERT(events & event);
    events = (Event)(events & ~event);
    EventContext& ctx = getContext(event);
    if (ctx.cb) {
        ctx.scheduler->schedule(&ctx.cb);
    } else {
        ctx.scheduler->schedule(&ctx.fiber);
    }
    ctx.scheduler = nullptr;
 }

IOManager::IOManager(size_t threads, bool use_caller, const std::string& name){
    //创建epoll实例
    m_epfd = epoll_create(5000);
    SYLAR_ASSERT(m_epfd > 0);
    //创建pipe，其中m_tickleFds[0]是读端，m_tickleFds[1]是管道的写端
    int rt = pipe(m_tickleFds);
    SYLAR_ASSERT(!rt);

    // 注册pipe读句柄的可读事件，用于tickle调度协程，通过epoll_event.data.fd保存描述符
    epoll_event event;
    memset(&event, 0, sizeof(epoll_event));
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = m_tickleFds[0];

    //设置为非阻塞方式，配合边缘触发
    rt = fcntl(m_tickleFds[0], F_SETFL, O_NONBLOCK);
    SYLAR_ASSERT(!rt);

    //将管道加入到epoll中，如果管道可读，那么idle中的epoll_wait会返回
    rt = epoll_ctl(m_epfd, EPOLL_CTL_ADD, m_tickleFds[0], &event);
    SYLAR_ASSERT(!rt);
    contextResize(32);
    start();
}

IOManager::~IOManager(){
    stop();
    close(m_epfd);
    close(m_tickleFds[0]);
    close(m_tickleFds[1]);
    
    for (size_t i = 0; i < m_fdContexts.size(); ++i){
        if (m_fdContexts[i]) {
            delete m_fdContexts[i];
        }
    }
}

void IOManager::contextResize(size_t size) {
    m_fdContexts.resize(size);
    for (size_t i = 0; i < m_fdContexts.size(); ++i){
        if (!m_fdContexts[i]){
            m_fdContexts[i] = new FdContext;
            m_fdContexts[i] -> fd = i;
        }
    }
}

/**
 * @brief 添加事件
 * @details fd描述符发生了event事件时执行cb函数
 * @param[in] fd socket句柄
 * @param[in] event 事件类型
 * @param[in] cb 事件回调函数，如果为空，则默认把当前协程作为回调执行体
 * @return 添加成功返回0,失败返回-1
 */
int IOManager::addEvent(int fd, Event event, std::function<void()> cb){
    FdContext* fd_ctx = nullptr;
    RWMutexType::ReadLock lock(m_mutex);
    if ((int)m_fdContexts.size() > (fd)) {
        fd_ctx = m_fdContexts[fd];
        lock.unlock();
    } else {
        lock.unlock();
        RWMutexType::WriteLock lock2(m_mutex);
        contextResize(fd * 1.5);
        fd_ctx = m_fdContexts[fd];
    }
    FdContext::MutexType::Lock lock2(fd_ctx->mutex);
    if (fd_ctx-> events & event) {
        SYLAR_LOG_ERROR(g_logger) << "addEvent assert fd=" << fd << " event="<< fd_ctx
        << "fd_ctx.event=" << fd_ctx->events;
        SYLAR_ASSERT(!(fd_ctx->events & event));
    }
    // 将新的事件加入epoll，使用epoll_event的私有指针存储FdContext的位置
    int op = fd_ctx->events ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
    epoll_event epevent;
    epevent.events = EPOLLET | fd_ctx->events | event;
    epevent.data.ptr = fd_ctx;
    int rt = epoll_ctl(m_epfd, op, fd, &epevent);
    if (rt) {
        SYLAR_LOG_ERROR(g_logger) << "epoll_ctl( " << m_epfd << ", "
        << op << " , " << fd << " , " << epevent.events << " ):"
        << rt << " (" << errno << ") (" << strerror(errno) << ")";
        return -1;
    }
    ++m_pendingEventCount;
    // 找到这个fd的event事件对应的EventContext，对其中的scheduler, cb, fiber进行赋值
    fd_ctx->events = (Event)(fd_ctx->events | event);
    FdContext::EventContext& event_ctx = fd_ctx->getContext(event);
    SYLAR_ASSERT(!event_ctx.scheduler && !event_ctx.fiber && !event_ctx.cb);
    event_ctx.scheduler = Scheduler::GetThis();
    // 赋值scheduler和回调函数，如果回调函数为空，则把当前协程当成回调执行体
    if (cb) {
        event_ctx.cb.swap(cb);
    } else {
        event_ctx.fiber = Fiber::GetThis();
        SYLAR_ASSERT(event_ctx.fiber->getState() == Fiber::EXEC);
    }
    return 0;
}

/**
 * @brief 删除事件
 * @param[in] fd socket句柄
 * @param[in] event 事件类型
 * @attention 不会触发事件
 * @return 是否删除成功
 */
bool IOManager::delEvent(int fd, Event event) {
    RWMutexType::ReadLock lock(m_mutex);
    if ((int)m_fdContexts.size() <= fd) {
        return false;
    }
    FdContext* fd_ctx = m_fdContexts[fd];
    lock.unlock();

    FdContext::MutexType::Lock lock2(fd_ctx->mutex);
    if (!(fd_ctx->events & event)){
        return false;
    }
    Event new_events = (Event)(fd_ctx->events & ~event);
    int op = new_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
    epoll_event epevent;
    epevent.events = EPOLLET | new_events;
    epevent.data.ptr = fd_ctx;

    int rt = epoll_ctl(m_epfd, op, fd, &epevent);
    if (rt) {
        SYLAR_LOG_ERROR(g_logger) << "epoll_ctl( " << m_epfd << ", "
        << op << " , " << fd << " , " << epevent.events << " ):"
        << rt << " (" << errno << ") (" << strerror(errno) << ")";
        return false;
    }
    --m_pendingEventCount;
    // 重置该fd对应的event事件上下文
    fd_ctx->events = new_events;
    FdContext::EventContext& event_ctx = fd_ctx->getContext(event);
    fd_ctx->resetContext(event_ctx);
    return true;
}

/**
 * @brief 取消事件
 * @param[in] fd socket句柄
 * @param[in] event 事件类型
 * @attention 如果该事件被注册过回调，那就触发一次回调事件
 * @return 是否删除成功
 */
bool IOManager::cancelEvent(int fd, Event event) {
    RWMutexType::ReadLock lock(m_mutex);
    if ((int)m_fdContexts.size() <= fd) {
        return false;
    }
    FdContext* fd_ctx = m_fdContexts[fd];
    lock.unlock();
    FdContext::MutexType::Lock lock2(fd_ctx->mutex);
    if (!(fd_ctx->events & event)){
        return false;
    }
    Event new_events = (Event)(fd_ctx->events & ~event);
    int op = new_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
    epoll_event epevent;
    epevent.events = EPOLLET | new_events;
    epevent.data.ptr = fd_ctx;

    int rt = epoll_ctl(m_epfd, op, fd, &epevent);
    if (rt) {
        SYLAR_LOG_ERROR(g_logger) << "epoll_ctl( " << m_epfd << ", "
        << op << " , " << fd << " , " << epevent.events << " ):"
        << rt << " (" << errno << ") (" << strerror(errno) << ")";
        return false;
    }
    //删除之前触发一次事件
    fd_ctx->triggerEvent(event);
    --m_pendingEventCount;
    return true;
}

/**
 * @brief 取消所有事件
 * @details 所有被注册的回调事件在cancel之前都会被执行一次
 * @param[in] fd socket句柄
 * @return 是否删除成功
 */
bool IOManager::cancelAll(int fd){
    RWMutexType::ReadLock lock(m_mutex);
    if ((int)m_fdContexts.size() <= fd) {
        return false;
    }
    FdContext* fd_ctx = m_fdContexts[fd];
    lock.unlock();
    FdContext::MutexType::Lock lock2(fd_ctx->mutex);
    if (!fd_ctx->events){
        return false;
    }

    int op = EPOLL_CTL_DEL;
    epoll_event epevent;
    epevent.events = 0;
    epevent.data.ptr = fd_ctx;

    int rt = epoll_ctl(m_epfd, op, fd, &epevent);
    if (rt) {
        SYLAR_LOG_ERROR(g_logger) << "epoll_ctl( " << m_epfd << ", "
        << op << " , " << fd << " , " << epevent.events << " ):"
        << rt << " (" << errno << ") (" << strerror(errno) << ")";
        return false;
    }
    // 取消前也要触发一次事件
    if (fd_ctx->events & READ) {
        fd_ctx->triggerEvent(READ);
        --m_pendingEventCount;
    }
    if (fd_ctx->events & WRITE){
        fd_ctx->triggerEvent(WRITE);
        --m_pendingEventCount;
    }
    SYLAR_ASSERT(fd_ctx->events == 0);
    return true;
}

IOManager* IOManager::GetThis(){
    return dynamic_cast<IOManager*>(Scheduler::GetThis());
}
void IOManager::tickle(){
    /**
     * @brief 通知调度器有任务要调度
     * @details 写pipe让idle协程从epoll_wait退出，待idle协程yield之后Scheduler::run就可以调度其他任务
     * 如果当前没有空闲调度线程，那就没必要发通知
     */
    if (!hasIdleThreads()) {
        return;
    }
    int rt = write(m_tickleFds[1], "T", 1);
    SYLAR_ASSERT(rt == 1);
}

bool IOManager::stopping(){
    uint64_t timeout = 0;
    return stopping(timeout);
}

bool IOManager::stopping(uint64_t& timeout){
    timeout = getNextTimer();
    // 对于IOManager而言，必须等所有待调度的IO事件都执行完了才可以退出
    return timeout == ~0ull && m_pendingEventCount == 0 && Scheduler::stopping();
}

void IOManager::idle() {
    /**
     * @brief idle协程
     * @details 对于IO协程调度来说，应阻塞在等待IO事件上，idle退出的时机是epoll_wait返回，对应的操作是tickle或注册的IO事件就绪
     * 调度器无调度任务时会阻塞idle协程上，对IO调度器而言，idle状态应该关注两件事，一是有没有新的调度任务，对应Schduler::schedule()，
     * 如果有新的调度任务，那应该立即退出idle状态，并执行对应的任务；二是关注当前注册的所有IO事件有没有触发，如果有触发，那么应该执行
     * IO事件对应的回调函数
     */
    epoll_event* events = new epoll_event[64]();
    std::shared_ptr<epoll_event> shared_events(events, [](epoll_event* ptr){
        delete[] ptr;
    });
    while(true) {
        uint64_t next_timeout = 0;
        if (stopping(next_timeout)) {
            SYLAR_LOG_INFO(g_logger) << "name=" << getName() << " idle stopping exit";
            break;
        }

        int rt = 0;
        do {
            static const int MAX_TIMEOUT = 5000;
            if (next_timeout != ~0ull) {
                next_timeout = (int)next_timeout > MAX_TIMEOUT ? MAX_TIMEOUT : next_timeout;
            } else {
                next_timeout = MAX_TIMEOUT;
            }
            rt = epoll_wait(m_epfd, events, 64, (int) next_timeout);
            if (rt < 0 && errno == EINTR) {
            } else {
                break;
            }
        } while (true);

        std::vector<std::function<void()>> cbs;
        listExpairedCb(cbs);
        if (!cbs.empty()) {
            schedule(cbs.begin(), cbs.end());
            cbs.clear();
        }
        // 遍历所有发生的事件，根据epoll_event的私有指针找到对应的FdContext，进行事件处理
        for (int i = 0; i < rt; i++) {
            epoll_event& event = events[i];
            if (event.data.fd == m_tickleFds[0]) {
                uint8_t dummy;
                // 因为采用了边缘触发模式，因此要尽量读完
                while (read(m_tickleFds[0], &dummy, 1) == 1);
                continue;
            }

            FdContext* fd_ctx = (FdContext*)event.data.ptr;
            FdContext::MutexType::Lock lock(fd_ctx->mutex);
            if (event.events & (EPOLLERR | EPOLLHUP)) {
                event.events |= EPOLLIN | EPOLLOUT;
            }
            int real_events = NONE;
            if (event.events & EPOLLIN) {
                real_events |= READ;
            }
            if (event.events & EPOLLOUT) {
                real_events |= WRITE;
            }

            if ((fd_ctx->events & real_events) == NONE){
                continue;
            }
            // 剔除已经发生的事件，将剩下的事件重新加入epoll_wait，
            // 如果剩下的事件为0，表示这个fd已经不需要关注了，直接从epoll中删除
            int left_events = (fd_ctx->events & ~real_events);
            int op = left_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
            event.events = EPOLLET | left_events;

            int rt2 = epoll_ctl(m_epfd, op, fd_ctx->fd, &event);
            if (rt2) {
                SYLAR_LOG_ERROR(g_logger) << "epoll_ctl( " << m_epfd << ", "
                << op << " , " << fd_ctx->fd << " , " << event.events << " ):"
                << rt << " (" << errno << ") (" << strerror(errno) << ")";
            }

            if (real_events & READ) {
                fd_ctx->triggerEvent(READ);
                --m_pendingEventCount;
            }
            if (real_events & WRITE) {
                fd_ctx->triggerEvent(WRITE);
                --m_pendingEventCount;
            }
        }
        /**
        * 一旦处理完所有的事件，idle协程yield，这样可以让调度协程(Scheduler::run)重新检查是否有新任务要调度
        * 上面triggerEvent实际也只是把对应的fiber重新加入调度，要执行的话还要等idle协程退出
        */
        Fiber::ptr cur = Fiber::GetThis();
        auto raw_ptr = cur.get();
        cur.reset();
        raw_ptr->swapOut();
    }
}

void IOManager::onTimerInsertedAtFront() {
    tickle();
}
}