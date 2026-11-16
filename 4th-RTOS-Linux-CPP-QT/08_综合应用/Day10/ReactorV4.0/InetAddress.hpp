#ifndef __InetAddress_H__
#define __InetAddress_H__

#include <func.h>

#include <string>

using std::string;

namespace wd
{

class InetAddress {
public:
    //0.0.0.0       //代表本机, 客户端可以在任意地方(远程)
    //127.0.0.1     //代表本机, 客户端和服务器都只能在本机
    InetAddress(unsigned short port, const string & ip = "127.0.0.1");
    //单参数的构造函数如果不希望发生隐式转换，都要加上explicit
    explicit InetAddress(struct sockaddr_in addr);

    string ip() const;
    unsigned short port() const;
    struct sockaddr_in * getInetAddressPtr() {  return &_addr;  }

private:
    struct sockaddr_in _addr;
};




}//end of namespace wd


#endif

