#ifndef __TcpConnection_H__
#define __TcpConnection_H__

#include "Noncopyable.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"
#include "SocketIO.hpp"

#include <string>
#include <memory>
#include <functional>
using std::string;
using std::shared_ptr;
using std::function;

namespace wd
{

class EventLoop;
class TcpConnection;
using TcpConnectionPtr=shared_ptr<TcpConnection>;
using TcpConnectionCallback=function<void(TcpConnectionPtr)>;

//Tcp连接是系统资源，不能进行复制，要表达对象语义
class TcpConnection : Noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd, EventLoop * loop);
    ~TcpConnection();
    //注册三个函数对象(回调函数)
    void setAllCallbacks(const TcpConnectionCallback & cb1,
                         const TcpConnectionCallback & cb2,
                         const TcpConnectionCallback & cb3)
    {
        _onConnection = cb1;//进行复制
        _onMessage = cb2;
        _onClose = cb3;
    }

    bool isClosed() const;
    string receive();
    void send(const string & msg);
    void sendInLoop(const string & msg);//通知IO线程进行发送
    string toString() const;

    //调用三个函数对象
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    Socket      _sock;
    SocketIO    _sockIO;
    InetAddress _localAddr;
    InetAddress _peerAddr;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
    EventLoop*  _loop;
};


}//end of namespace wd


#endif

