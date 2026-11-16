#ifndef __Acceptor_H__
#define __Acceptor_H__

#include "InetAddress.hpp"
#include "Socket.hpp"

namespace wd
{


class Acceptor
{
public:
    Acceptor(unsigned short port, const string & ip = "0.0.0.0");
    void ready();

    int accept();
private:
    void setReuseAddr(bool);
    void setReusePort(bool);
    void bind();
    void listen();

private:
    InetAddress _addr;
    Socket _listensock;
};

}//end of namespace wd


#endif

