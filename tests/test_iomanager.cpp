#include "slinnr/sylar.h"
#include "slinnr/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>


sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

int sock = 0;

void test_fiber() {
   
    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "110.242.68.3", &addr.sin_addr.s_addr);

    if (!connect(sock, (const sockaddr*)&addr, sizeof(addr))){

    }else if (errno == EINPROGRESS)
    {
        SYLAR_LOG_INFO(g_logger) << "add event errno= " << errno << " " << strerror(errno);
        sylar::IOManager::GetThis() -> addEvent(sock, sylar::IOManager::READ, [](){
            SYLAR_LOG_INFO(g_logger) << "read callback";
        });
        sylar::IOManager::GetThis() -> addEvent(sock, sylar::IOManager::WRITE, [](){
            SYLAR_LOG_INFO(g_logger) << "wirte callback";
            // close(sock);
            sylar::IOManager::GetThis() -> cancelEvent(sock, sylar::IOManager::READ);
        });
    } else {
        SYLAR_LOG_INFO(g_logger) << "else" << errno << " " << strerror(errno);
    }
}

void test_timer() {
    sylar::IOManager iom(2);
    iom.addTimer(500, [](){
        SYLAR_LOG_INFO(g_logger) << "hello timer";
    }, true);
}

int main(int argc, char** argv) {
    // sylar::IOManager iom;
    // iom.schedule(&test_fiber);
    test_timer();
    return 0;
}
