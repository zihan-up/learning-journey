#ifndef __TcpServer_H__
#define __TcpServer_H__

#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include "EventLoop.hpp"

namespace wd
{

class TcpServer
{
public:
    TcpServer(unsigned short port, const string & ip = "127.0.0.1")
    : _acceptor(port, ip)
    , _loop(_acceptor)
    {   _acceptor.ready();  }

    void setAllCallbacks(TcpConnectionCallback && cb1,
                         TcpConnectionCallback && cb2,
                         TcpConnectionCallback && cb3)
    {
        _loop.setAllCallbacks(std::move(cb1),
                              std::move(cb2),
                              std::move(cb3));
    }

    void start() {
        _loop.loop();
    }

    //stop函数一定要与start函数运行在不同的线程
    void stop()
    {
        _loop.unloop();
    }
    
private:
    Acceptor    _acceptor;
    EventLoop   _loop;
};

}//end of namespace wd


#endif

