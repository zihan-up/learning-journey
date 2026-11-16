#ifndef __Socket_H__
#define __Socket_H__
#include "Noncopyable.hpp"

namespace wd
{


//套接字是系统资源，一般情况下不能进行复制
class Socket
: Noncopyable //可以表达语义
{
public:
    Socket();
    explicit Socket(int);
    ~Socket();

    void shutdownWrite();

    int fd() const { return _fd; }

private:
    int _fd;
};

}//end of namspace wd


#endif

