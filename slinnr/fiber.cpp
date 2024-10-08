#include "fiber.h"
#include "schedule.h"

namespace sylar {

static Logger::ptr g_logger = SYLAR_LOG_NAME("system");

static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

static thread_local Fiber* t_fiber = nullptr; //当前线程正在运行的写成
static thread_local Fiber::ptr t_threadFiber = nullptr; // 当前线程的主协程

static ConfigVar<uint32_t>::ptr g_fiber_stack_size = 
        Config::Lookup<uint32_t>("fiber.stack_size", 1024 * 1024, "fiber stack size");


class MallocStackAllocator {
public:
    static void* Alloc(size_t size) {
        return malloc(size);
    }

    static void Dealoc(void* vp, size_t) {
        return free(vp);
    }
};

using StackAllocator = MallocStackAllocator;

Fiber::Fiber() {
    m_state = EXEC;
    SetThis(this);
    if (getcontext (&m_ctx)) {
        SYLAR_ASSERT2(false, "getcontext");
    }
    SYLAR_LOG_INFO(g_logger) << "FIber::Fiber id = " << m_id;
    ++s_fiber_count;
}

Fiber::Fiber(std::function<void()> cb, size_t stacksize, bool use_caller)
    :m_id(++s_fiber_id)
    ,m_cb(cb) {
    ++s_fiber_count;
    m_stacksize = stacksize? stacksize : g_fiber_stack_size->getValue();

    m_stack = StackAllocator::Alloc(m_stacksize);
    if (getcontext(&m_ctx)) {
        SYLAR_ASSERT2(false, "getcontext");
    }
    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_stacksize;

    if (!use_caller) {
        makecontext(&m_ctx, &Fiber::MainFunc, 0);
    }else{
        makecontext(&m_ctx, &Fiber::CallerMainFunc, 0);
    }
    SYLAR_LOG_INFO(g_logger) << "FIber::Fiber id = " << m_id;
}

Fiber::~Fiber() {
    -- s_fiber_count;
    if (m_stack) {
        SYLAR_ASSERT(m_state == TERM || m_state == INIT || m_state == EXCEPT);
        StackAllocator::Dealoc(m_stack, m_stacksize);
    }else {
        SYLAR_ASSERT(!m_cb);
        SYLAR_ASSERT(m_state == EXEC);
        Fiber * cur = t_fiber;
        if (cur == this) {
            SetThis(nullptr);
        }
    }
    SYLAR_LOG_DEBUG(g_logger) << "fiber ~fiber id= " << m_id;
}

//重置协程函数，并重置状态
void Fiber::reset(std::function<void()> cb){
    SYLAR_ASSERT(m_stack);
    SYLAR_ASSERT(m_state == TERM || m_state == INIT || m_state == EXCEPT);
    m_cb = cb;
    if (getcontext(&m_ctx)) { 
        SYLAR_ASSERT2(false, "getcontext");
    }
    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_stacksize;
    makecontext(&m_ctx, &Fiber::MainFunc, 0);
    m_state = INIT;
}

//切换到当前协程执行
void Fiber::swapIn(){
    SetThis(this);
    SYLAR_ASSERT(m_state != EXEC);
    m_state = EXEC;
    if (swapcontext(&Scheduler::GetMainFiber() -> m_ctx, &m_ctx)) {
        SYLAR_ASSERT2(false, "swapcontext");
    }
}
//切换到后台执行
void Fiber::swapOut() {
    SetThis(Scheduler::GetMainFiber());
    if (swapcontext(&m_ctx, &Scheduler::GetMainFiber() -> m_ctx) ) {
            SYLAR_ASSERT2(false, "swapcontext");
        }    
}

void Fiber::call() {
    SetThis(this);
    m_state = EXEC;
    if(swapcontext(&t_threadFiber->m_ctx, &m_ctx)) {
        SYLAR_ASSERT2(false, "swapcontext");
    }
}

void Fiber::back() {
    SetThis(t_threadFiber.get());
    if(swapcontext(&m_ctx, &t_threadFiber->m_ctx)) {
        SYLAR_ASSERT2(false, "swapcontext");
    }
}


void Fiber::SetThis(Fiber* f){
    t_fiber = f;
}

//返回当前协程
Fiber::ptr Fiber::GetThis() {
    if (t_fiber) {
        return t_fiber -> shared_from_this();
    }
    Fiber::ptr main_fiber(new Fiber);
    SYLAR_ASSERT(t_fiber == main_fiber.get());
    t_threadFiber = main_fiber;
    return t_fiber -> shared_from_this();
}

//协程切换到后台，并且设置为Read状态
void Fiber::YieldToReady() {
    Fiber::ptr cur = GetThis();
    cur->m_state = READY;
    cur->swapOut();
}
//协程切换到后台，并且设置为Hold状态
void Fiber::YieldToHold() {
    Fiber::ptr cur = GetThis();
    cur -> m_state = HOLD;
    cur->swapOut();
}
//总协程数
uint64_t Fiber::TotalFibers() {
    return s_fiber_count;
}

uint64_t Fiber::GetFiberId(){
    if (t_fiber) {
        return t_fiber -> getId();
    }
    return 0;
}


void Fiber::MainFunc(){
    Fiber::ptr cur = GetThis();
    SYLAR_ASSERT(cur);
    try {
        cur -> m_cb();
        cur -> m_cb = nullptr;
        cur -> m_state = TERM;
    } catch (std::exception& ex) {
        cur -> m_state = EXCEPT;
        SYLAR_LOG_ERROR(g_logger) << "Fiber Except: " << ex.what();
    }catch (...) {
        cur -> m_state = EXCEPT;
        SYLAR_LOG_ERROR(g_logger) << "Fiber Except";
    }
    auto raw_ptr = cur.get();
    cur.reset();
    raw_ptr -> swapOut();   

    SYLAR_ASSERT2(false, "never reach fiber_id = " + std::to_string(raw_ptr->getId())) ;
}

void Fiber::CallerMainFunc(){
    Fiber::ptr cur = GetThis();
    SYLAR_ASSERT(cur);
    try {
        cur -> m_cb();
        cur -> m_cb = nullptr;
        cur -> m_state = TERM;
    } catch (std::exception& ex) {
        cur -> m_state = EXCEPT;
        SYLAR_LOG_ERROR(g_logger) << "Fiber Except: " << ex.what();
    }catch (...) {
        cur -> m_state = EXCEPT;
        SYLAR_LOG_ERROR(g_logger) << "Fiber Except";
    }
    auto raw_ptr = cur.get();
    cur.reset();
    raw_ptr -> back();   

    SYLAR_ASSERT2(false, "never reach fiber_id = " + std::to_string(raw_ptr->getId())) ;
}
}