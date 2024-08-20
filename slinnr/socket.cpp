#include "socket.h"
#include "iomanager.h"
#include "fd_manager.h"
#include "log.h"
#include "macro.h"
#include "hook.h"
#include <limits.h>

namespace sylar {

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

Socket::ptr Socket::CreateTCP(sylar::Address::ptr address) {
    Socket::ptr socket(new Socket(address->getFamily(), TCP, 0));
    return socket;
}

Socket::ptr Socket::CreateUDP(sylar::Address::ptr address) {
    Socket::ptr socket(new Socket(address->getFamily(), UDP, 0));
    initSock();
    socket->isConnected = true; //UDP没有建立链接步骤，因此直接初始化为已连接
    return socket;
}

Socket::ptr Socket::CreateTCPSocket() {
    Socket::ptr socket(new Socket(IPv4), TCP, 0);
    return socket;
}

Socket::ptr Socket::CreateUDPSocket() {
    Socket::ptr socket(new Socket(IPv4, UDP, 0));
    initSock();
    socket->isConnected = true;
    return socket;
}

Socket::ptr Socket::CreateTCPSocket6() {
}

Socket::ptr Socket::CreateUDPSocket6() {
}

Socket::ptr Socket::CreateUnixTCPSocket() {
}

Socket::ptr Socket::CreateUnixUDPSocket() {
}

Socket::Socket(int family, int type, int protocol)
    :m_family(m_family)
    ,m_type(type)
    ,m_protocol(protocol)
    ,m_sock(-1)
    ,m_isConnected(false){

}

Socket::~Socket() {
}

int64_t Socket::getSendTimeout() {
}

void Socket::setSendTimeout(int64_t v) {
}

int64_t Socket::getRecvTimeout() {
}

void Socket::setRecvTimeout(int64_t v) {
}

bool Socket::getOption(int level, int option, void* result, socklen_t* len) {
}

bool Socket::setOption(int level, int option, const void* result, socklen_t len) {
   if (setsockopt(m_sock, level, option, result, (socklen_t)len)) {
        SYLAR_LOG_DEBUG(g_logger) << "setOption sock=" << m_sock
        << " level=" << level << " option=" << option
        << " errno=" << errno << " errstr=" << strerror(errno);
        return false;
   }
   return true;
}

Socket::ptr Socket::accept() {
   
}

bool Socket::init(int sock) {
   
}

bool Socket::bind(const Address::ptr addr) {
   
}

bool Socket::reconnect(uint64_t timeout_ms) {
   
}

bool Socket::connect(const Address::ptr addr, uint64_t timeout_ms) {
   
}

bool Socket::listen(int backlog) {
    
}

bool Socket::close() {
   
}

int Socket::send(const void* buffer, size_t length, int flags) {
   
}

int Socket::send(const iovec* buffers, size_t length, int flags) {
    
}

int Socket::sendTo(const void* buffer, size_t length, const Address::ptr to, int flags) {
    
}

int Socket::sendTo(const iovec* buffers, size_t length, const Address::ptr to, int flags) {
   
}

int Socket::recv(void* buffer, size_t length, int flags) {
    
}

int Socket::recv(iovec* buffers, size_t length, int flags) {
    
}

int Socket::recvFrom(void* buffer, size_t length, Address::ptr from, int flags) {
    
}

int Socket::recvFrom(iovec* buffers, size_t length, Address::ptr from, int flags) {
    
}

Address::ptr Socket::getRemoteAddress() {
    
}

Address::ptr Socket::getLocalAddress() {

}

bool Socket::isValid() const {
}

int Socket::getError() {

}

std::ostream& Socket::dump(std::ostream& os) const {

}

std::string Socket::toString() const {

}

bool Socket::cancelRead() {
}

bool Socket::cancelWrite() {
}

bool Socket::cancelAccept() {
}

bool Socket::cancelAll() {
}

void Socket::initSock() {
    int val = 1;
    setOption(SOL_SOCKET, SO_REUSEADDR, val);
    if (m_type == SOCK_STREAM) {
        setOption(IPPROTO_TCP, TCP_NODELAY, val);
    }
}

void Socket::newSock() {
    m_sock = socket(m_family, m_type, m_protocol);
    if (m_sock != -1) {
        initSock();
    } else {
        SYLAR_LOG_ERROR(g_logger) << "“socket create failed";
    }
}

namespace {

struct _SSLInit {
    _SSLInit() {
        SSL_library_init();
        SSL_load_error_strings();
        OpenSSL_add_all_algorithms();
    }
};

static _SSLInit s_init;

}

SSLSocket::SSLSocket(int family, int type, int protocol)
}

Socket::ptr SSLSocket::accept() {

}

bool SSLSocket::bind(const Address::ptr addr) {
    return Socket::bind(addr);
}

bool SSLSocket::connect(const Address::ptr addr, uint64_t timeout_ms) {

}

bool SSLSocket::listen(int backlog) {
}

bool SSLSocket::close() {
}

int SSLSocket::send(const void* buffer, size_t length, int flags) {

}

int SSLSocket::send(const iovec* buffers, size_t length, int flags) {

}

int SSLSocket::sendTo(const void* buffer, size_t length, const Address::ptr to, int flags) {
}

int SSLSocket::sendTo(const iovec* buffers, size_t length, const Address::ptr to, int flags) {

}

int SSLSocket::recv(void* buffer, size_t length, int flags) {

}

int SSLSocket::recv(iovec* buffers, size_t length, int flags) {

}

int SSLSocket::recvFrom(void* buffer, size_t length, Address::ptr from, int flags) {
}

int SSLSocket::recvFrom(iovec* buffers, size_t length, Address::ptr from, int flags) {
}

bool SSLSocket::init(int sock) {

}

bool SSLSocket::loadCertificates(const std::string& cert_file, const std::string& key_file) {

}

SSLSocket::ptr SSLSocket::CreateTCP(sylar::Address::ptr address) {
}

SSLSocket::ptr SSLSocket::CreateTCPSocket() {
}

SSLSocket::ptr SSLSocket::CreateTCPSocket6() {
}

std::ostream& SSLSocket::dump(std::ostream& os) const {
    
}

std::ostream& operator<<(std::ostream& os, const Socket& sock) {
}

}
