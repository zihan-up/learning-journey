#ifndef __TcpConnection_H__
#define __TcpConnection_H__

#include "Noncopyable.hpp"
#include "Socket.hpp"
#include "SocketIO.hpp"
#include "InetAddress.hpp"


namespace wd
{

class TcpConnection
: Noncopyable
{
public:
    TcpConnection(int fd);

    void send(const string & msg);
    string receive();
    string toString() const;

    void shutdown();

private:
    InetAddress getLocalAddress() const;
    InetAddress getPeerAddress() const;

private:
    Socket _sock;
    SocketIO _socketIO;
    InetAddress _localAddr;
    InetAddress _peerAddr;
};

}//end of namespace wd


#endif

