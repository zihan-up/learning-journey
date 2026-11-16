#include "SocketIO.hpp"

#include <func.h>

#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

SocketIO::SocketIO(int fd)
: _fd(fd)
{}

//确定要发送len字节的数据
int SocketIO::sendn(const char * buff, int len)
{
    int left = len;
    const char * pbuf = buff;
    while(left > 0) {
        int ret = send(_fd, pbuf, left, 0);
        if(ret < 0) {
            perror("send");
            return len - left;
        }

        left -= ret;
        pbuf += ret;
    }

    return len;
}

//确定接收len字节的数据
int SocketIO::recvn(char * buff, int len)
{
    int left = len;
    char * pbuf = buff;
    while(left > 0) {
        int ret = recv(_fd, pbuf, left, 0);
        if(ret == -1 && errno == EINTR) {
            continue;
        } else if(ret == 0) {
            //连接断开了
            return len - left;
        } else if(ret == -1) {
            perror("recv");
            return len - left;
        }

        left -= ret;
        pbuf += ret;
    }
    return len;
}

//一次获取一行数据
//max表示的是一行数据的最大字节数
//但最后一个字节不能用来存数据，应该存 '\0'
int SocketIO::readline(char * buff, int max)
{
    int left = max - 1;
    char * pbuf = buff;
    int total = 0;
    while(left > 0) {
        int ret = recv(_fd, pbuf, left, MSG_PEEK);

        //在读取到ret个字节中查找'\n'
        for(int i = 0; i < ret; ++i) {
            if(pbuf[i] == '\n') {
                //找到了'\n'
                int sz = i + 1;
                recvn(pbuf, sz);
                pbuf[i] = '\0';
                total += i;
                return total;
            }
        }
        //没有找到'\n', 从内核缓冲区中移走
        ret = recvn(pbuf, ret);
        left -= ret;
        pbuf += ret;
        total += ret;
    }
    return max - 1;
}

}//end of namespace wd
