#ifndef __BussinessService_H__
#define __BussinessService_H__

#include "TcpConnection.hpp"

#include <iostream>
using std::cout;
using std::endl;


class Mytask
{
public:
    Mytask(const string &msg, wd::TcpConnectionPtr conn)
    : _msg(msg)
    , _conn(conn)
    {}

    //打包成一个回调函数，交给线程池中的计算线程执行
    void process() {
        cout << "\ncompute thread << " << pthread_self() 
             << ", Mytask::process is running" << endl;
        //执行业务逻辑
        //decode
        //compute
        //encode
        string response = _msg;
        //发送消息,一定要依赖于TcpConnection对象
        //直接完成了消息的发送
        //问题：从设计的角度来看，消息的发送应该要在
        //IO线程中完成，不能在计算线程中完成,此版本
        //没有做到职责分离：数据的收发与业务逻辑的计算
        //没有分离, 需要继续优化
        //_conn->send(response);
        _conn->sendInLoop(response);
    }

private:
    string _msg;
    wd::TcpConnectionPtr _conn;
};


#endif

