#include "TcpConnection.hpp"
#include <sstream>


namespace wd
{


TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _sockIO(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
{

}
    
bool TcpConnection::isClosed() const
{
    char buff[20] = {0};
    int ret = _sockIO.recvPeek(buff, sizeof(buff));
    return ret == 0;
}

//一个TCP连接的核心功能就是用来收发数据
string TcpConnection::receive()
{   //该函数每一次读取一行数据
    char buff[65535] = {0};//栈上开辟64KB的空间
    int ret = _sockIO.readline(buff, sizeof(buff));
    return string(buff, ret);
}

void TcpConnection::send(const string & msg)
{
    //发送消息
    int ret = _sockIO.sendn(msg.data(), msg.size());
    printf(">> send %d bytes.\n", ret);
}
    
string TcpConnection::toString() const
{
    std::ostringstream oss;
    oss << "tcp " << _localAddr.ip() << ":" << _localAddr.port()
        << " -> " << _peerAddr.ip() << ":" << _peerAddr.port();
    return oss.str();
}

InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);//这里必须要赋值,如果参数值不正确，会报错
    memset(&addr, 0, sizeof(addr));
    int ret = getsockname(_sock.fd(), (struct sockaddr*)&addr, &len);
    if(ret < 0) {
        perror("getsockname");
    }
    return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);//这里必须要赋值,如果参数值不正确，会报错
    memset(&addr, 0, sizeof(addr));
    int ret = getpeername(_sock.fd(), (struct sockaddr*)&addr, &len);
    if(ret < 0) {
        perror("getpeername");
    }
    return InetAddress(addr);
}

}//end of namespace wd
