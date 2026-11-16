#include "Socket.hpp"
#include <func.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

Socket::Socket()
{
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if(_fd < 0) {
        perror("socket");
    }
}
    
Socket::Socket(int fd)
: _fd(fd)
{
}
    
Socket::~Socket()
{
    close(_fd);
    cout << "socket " << _fd << " has closed" << endl;
}

    
//主动关闭连接时，使用该函数
void Socket::shutdownWrite()
{
    shutdown(_fd, SHUT_WR);
}



}//end of namespace wd
