#ifndef __TcpConnection_H__
#define __TcpConnection_H__

#include "Noncopyable.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"
#include "SocketIO.hpp"

#include <string>
using std::string;

namespace wd
{

//Tcp连接是系统资源，不能进行复制，要表达对象语义
class TcpConnection : Noncopyable
{
public:
    explicit
    TcpConnection(int fd);

    bool isClosed() const;
    string receive();
    void send(const string & msg);
    string toString() const;


private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    Socket      _sock;
    SocketIO    _sockIO;
    InetAddress _localAddr;
    InetAddress _peerAddr;
};


}//end of namespace wd


#endif

