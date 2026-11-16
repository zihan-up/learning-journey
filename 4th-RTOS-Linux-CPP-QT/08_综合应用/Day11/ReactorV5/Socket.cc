
#include "Socket.hpp"
#include <func.h>

namespace wd
{

Socket::Socket()
: _fd(-1)
{
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if(_fd < 0) {
        perror("socket");
    }
}

Socket::~Socket()
{
    if(_fd > 0) {
        close(_fd);
    }
}

void Socket::shuntdonwWrite()
{
    //只关闭写端，在主动断开连接时使用
    shutdown(_fd, SHUT_WR);
}
}//end of namespace wd
