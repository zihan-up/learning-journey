#ifndef __Socket_H__
#define __Socket_H__

#include "Noncopyable.hpp"


namespace wd
{

//利用RAII的技术管理套接字资源
//不可以进行复制,也是系统资源
class Socket : Noncopyable
{
public:
    Socket();

    //加上explicit关键字是为了禁止隐式转换
    explicit
    Socket(int fd) 
    : _fd(fd)
    {}

    ~Socket();
    void shuntdonwWrite();

    int fd() const {    return _fd; }

private:
    int _fd;
};

}//end of namespace wd


#endif

