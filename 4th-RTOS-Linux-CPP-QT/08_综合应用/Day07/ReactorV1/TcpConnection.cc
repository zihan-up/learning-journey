#include "TcpConnection.hpp"

#include <sstream>

namespace wd
{

TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _socketIO(fd)
, _localAddr(getLocalAddress())
, _peerAddr(getPeerAddress())
{

}

    
void TcpConnection::send(const string & msg)
{
    _socketIO.sendn(msg.c_str(), msg.size());
}
    
//读取一行数据, 传输过来的数据中一定要携带'\n'，
//否则代码会在这里卡住
string TcpConnection::receive()
{
    char buff[65536] = {0};
    int ret = _socketIO.readline(buff, sizeof(buff));
    return string(buff, ret);
}

//主动关闭连接
void TcpConnection::shutdown()
{
    _sock.shutdownWrite();
}


InetAddress TcpConnection::getLocalAddress() const
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t len = sizeof(addr);
    int ret = getsockname(_sock.fd(), (struct sockaddr*)&addr, &len);
    if(ret < 0) {
        perror("getsockname");
    }
    return InetAddress(addr);
}
    

InetAddress TcpConnection::getPeerAddress() const
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t len = sizeof(addr);
    int ret = getpeername(_sock.fd(), (struct sockaddr*)&addr, &len);
    if(ret < 0) {
        perror("getpeername");
    }
    return InetAddress(addr);

}
    
string TcpConnection::toString() const
{
    std::ostringstream oss;
    oss << "> tcp socket " << _sock.fd() 
        << ", " << _localAddr.ip() << ":" << _localAddr.port()
        << "->"      << _peerAddr.ip() << ":" << _peerAddr.port();
    return oss.str();
    
}

}//end of namespace wd
