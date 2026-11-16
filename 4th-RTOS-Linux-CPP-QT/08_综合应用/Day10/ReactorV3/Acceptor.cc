#include "Acceptor.hpp"
#include <asm-generic/socket.h>
#include <sys/socket.h>


namespace wd
{

Acceptor::Acceptor(unsigned short port, const string & ip)
: _addr(port, ip)
, _listensock()
{}

void Acceptor::ready()
{
    setReuseAddr(true);
    setReusePort(true);
    bind();
    listen();
}
    
int Acceptor::accept()
{
    int netfd = ::accept(fd(), nullptr, nullptr);
    if(netfd < 0) {
        perror("accept");
    }
    return netfd;
}

void Acceptor::setReuseAddr(bool on)
{
    int one = on;
    int ret = setsockopt(fd(), SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(ret < 0) {
        perror("setsockopt");
    }
}

//设置端口可以重用, 服务器程序可以在同一台机器上启动多个进程
void Acceptor::setReusePort(bool on)
{
    int one = on;
    int ret = ::setsockopt(fd(), SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one));
    if(ret < 0) {
        perror("setsockopt");
    }
}

void Acceptor::bind()
{
    //这样写，相当于是自身的递归调用
    //int ret = bind(fd(), (struct sockaddr*)_addr.getInetAddressPtr(), sizeof(_addr));
    //使用匿名命名空间就可以解决调用Linux下的接口的问题
    int ret = ::bind(fd(), (struct sockaddr*)_addr.getInetAddressPtr(), sizeof(_addr));
    if(ret < 0) {
        perror("bind");
    }
}

void Acceptor::listen()
{
    int ret = ::listen(fd(), 20000);
    if(ret < 0) {
        perror("listen");
    }
}


}// end of namespace wd
