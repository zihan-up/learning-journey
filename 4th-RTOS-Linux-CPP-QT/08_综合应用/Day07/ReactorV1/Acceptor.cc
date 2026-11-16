#include "Acceptor.hpp"
#include <asm-generic/socket.h>


namespace wd
{

Acceptor::Acceptor(unsigned short port, const string & ip)
: _addr(port, ip)
, _listensock()
{

}

void Acceptor::ready()
{
    setReuseAddr(true);
    setReusePort(true);
    bind();
    listen();
}

void Acceptor::setReuseAddr(bool on)
{
    int one = on ? 1 : 0;
    int ret = setsockopt(_listensock.fd(), SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(ret < 0) {
        perror("setsockopt");
    }
}

void Acceptor::setReusePort(bool on)
{
    int one = on ? 1 : 0;
    int ret = setsockopt(_listensock.fd(), SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one));
    if(ret < 0) {
        perror("setsockopt");
    }
}

void Acceptor::bind()
{
    //要调用的Linux下的bind接口，必须要加上匿名命名空间
    int ret = ::bind(_listensock.fd(), (const struct sockaddr*)_addr.getAddrPtr(),
                   sizeof(_addr));
    if(ret < 0) {
        perror("bind");
    }
}

void Acceptor::listen()
{
    int ret = ::listen(_listensock.fd(), 20000);
    if(ret < 0) {
        perror("listen");
    }
}

int Acceptor::accept()
{
    int peerfd = ::accept(_listensock.fd(), nullptr, nullptr);
    if(peerfd < 0) {
        perror("accept");
    }
    return peerfd;
}


}//end of namespace wd
