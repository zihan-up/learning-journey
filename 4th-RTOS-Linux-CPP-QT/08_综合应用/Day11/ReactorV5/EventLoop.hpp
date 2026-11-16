#ifndef __EventLoop_H__
#define __EventLoop_H__

#include "TcpConnection.hpp"
#include "MutexLock.hpp"

#include <sys/epoll.h>

#include <vector>
#include <map>

using std::vector;
using std::map;

namespace wd
{

using Functor=std::function<void()>;
class Acceptor;//类的前向声明

class EventLoop
{
public:
    EventLoop(Acceptor &);
    ~EventLoop();

    //注册三个函数对象(回调函数),为了转交给TcpConnection对象
    void setAllCallbacks(TcpConnectionCallback && cb1,
                         TcpConnectionCallback && cb2,
                         TcpConnectionCallback && cb3)
    {
        _onConnection = std::move(cb1);
        _onMessage = std::move(cb2);
        _onClose = std::move(cb3);
    }

    void loop();
    void unloop() { _isLooping = false; }
    void runInLoop(Functor && f);
private:
    int createEpollFd();
    void addEpollReadEvent(int);
    void delEpollReadEvent(int);

    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int);

    int createEventFd();
    void handleReadEvent();
    void wakeup();
    void doPendingFunctors();

private:
    int                         _epfd;
    int                         _eventfd;
    Acceptor &                  _acceptor;
    bool                        _isLooping;
    vector<struct epoll_event>  _evtArr;

    map<int, TcpConnectionPtr>  _conns;//管理已经建立好的TCP连接

    TcpConnectionCallback       _onConnection;
    TcpConnectionCallback       _onMessage;
    TcpConnectionCallback       _onClose;
    vector<Functor>             _pendingFunctors;//存储的是待发送的消息
    MutexLock                   _mutex;

};


}//end of namespace wd



#endif

