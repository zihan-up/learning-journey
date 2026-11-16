#include "TcpConnection.hpp"
#include "TcpServer.hpp"
#include "Threadpool.hpp"
#include <iostream>

using std::cout;
using std::endl;


//全局的线程池对象
wd::Threadpool threadpool(4, 10);

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
        _conn->send(response);
    }

private:
    string _msg;
    wd::TcpConnectionPtr _conn;
};

//连接建立时要做的事儿
void onConnection(wd::TcpConnectionPtr conn)
{
    cout << "ReactorV4.0: " << conn->toString() << " has connected successfully." << endl;
}

//消息到达时要执行的业务逻辑
//运行在IO线程(Reactor所在的线程)
void onMessage(wd::TcpConnectionPtr conn)
{
    //接收消息
    string msg = conn->receive();
    cout << "\nio thread " << pthread_self() 
         << ", recv msg:" << msg << endl;
    //将消息封装成一个任务，交给线程池执行
    Mytask mytask(msg, conn);
    threadpool.addTask(std::bind(&Mytask::process, mytask));
}

//连接断开时要做的事儿
void onClose(wd::TcpConnectionPtr conn)
{
    cout << "ReactorV3:" << conn->toString() << " has closed." << endl;
}


int main()
{
    threadpool.start();//开始运行线程池

    wd::TcpServer server(8000);
    printf(">> server start listening.\n");

    //设置三个回调函数
    server.setAllCallbacks(onConnection, onMessage, onClose);
    //服务器开始事件循环
    server.start();

    return 0;
}

