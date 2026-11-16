#include "SocketIO.hpp"
#include <func.h>
namespace wd
{

//查看内核接收缓冲区是否有数据
int SocketIO::recvPeek(char * buff, int len) const
{
    int ret = -1;
    do{
        ret = recv(_fd, buff, len, MSG_PEEK);
    }while(ret == -1 && errno == EINTR);
    return ret;
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
        } else if (ret == -1) {
            perror("recv");
            return len - left;
        } else if(ret == 0) {
            //代表连接断开了, 但这里不适合
            //做关闭套接字的事儿, 因为该操作是Socket的事儿
            return len - left;
        } else {
            left -= ret;
            pbuf += ret;
        }
    }
    return len - left;
}

//一行数据的字节数是不确定的，只跟'\n'有关
//char buff[1000] = {0};
int SocketIO::readline(char * buff, int maxlen)
{
    //预留缓冲区最后一个位置的值，设为'\0'
    //防止出现数组访问越界的情况
    char * pbuf = buff;
    int left = maxlen - 1;
    int total = 0;//用来记录一共读取的字节数
    while(left > 0) {
        //查看内核接收缓冲区的数据，但并不移走
        int ret = recvPeek(pbuf, left);

        //在ret个字节的数据中查找是否有'\n'
        for(int i = 0; i < ret; ++i) {
            if(pbuf[i] == '\n') {
                //找到了'\n'
                int sz = i + 1;
                ret = recvn(pbuf, sz);
                total += ret;
                pbuf[i] = '\0';//将'\n'设置为'\0'
                return total;
            }
        }

        //没有找到'\n'
        ret = recvn(pbuf, ret);
        left -= ret;
        pbuf += ret;
        total += ret;
    }
    //查找了好多次，达到了一行数据的上限，还是没有找到'\n'
    buff[maxlen - 1] = '\0';
    return maxlen - 1;
}

//确定发送len字节的数据
int SocketIO::sendn(const char * buff, int len)
{
    int left = len;
    const char * pbuf = buff;
    while(left > 0) {
        int ret = send(_fd, pbuf, left, 0);
        if(ret == -1 && errno == EINTR) {
            continue;
        } else if (ret == -1) {
            perror("send");
            return len - left;
        } else {
            left -= ret;
            pbuf += ret;
        }
    }
    return len - left;
}


}//end of namespace wd
