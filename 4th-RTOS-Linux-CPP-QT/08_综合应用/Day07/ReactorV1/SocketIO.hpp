#ifndef __SocketIO_H__
#define __SocketIO_H__

namespace wd
{


class SocketIO
{
public:
    SocketIO(int fd);

    int sendn(const char * buff, int len);
    int recvn(char * buff, int len);

    //一次获取一行数据
    int readline(char * buff, int max);

private:
    int _fd;
};



}//end of namespace wd


#endif

