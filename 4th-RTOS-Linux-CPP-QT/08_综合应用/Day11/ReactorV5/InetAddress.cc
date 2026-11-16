#include "InetAddress.hpp"


namespace wd
{


//默认参数只需要在函数申明中出现，不需要在定义中出现
InetAddress::InetAddress(unsigned short port, const string & ip)
{
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_port = htons(port);
}
    
InetAddress::InetAddress(struct sockaddr_in addr)
: _addr(addr)
{}

string InetAddress::ip() const
{
    return string(inet_ntoa(_addr.sin_addr));
}
    
unsigned short InetAddress::port() const
{
    return ntohs(_addr.sin_port);
}

}//end of namespace wd
