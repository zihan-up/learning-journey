#ifndef __Acceptor_H__
#define __Acceptor_H__

#include "InetAddress.hpp"
#include "Socket.hpp"
#include <sys/stat.h>

namespace wd
{

class Acceptor
{
public:
    //在类内部只有申明，没有实现的，这都是非inline函数
    Acceptor(unsigned short port, const string & ip = "127.0.0.1");
    void ready();
    int accept();
    //在类内部实现的都是inline函数
    int fd() const {    return _listensock.fd();    }
    //int fd() const;// {    return _listensock.fd();    }

private:
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();
    void listen();

private:
    InetAddress _addr;
    Socket _listensock;
};

//不是Inline函数
//int Acceptor::fd() const {    return _listensock.fd();    }


}//end of namespace wd


#endif

