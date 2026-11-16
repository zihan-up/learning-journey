#include "Acceptor.hpp"
#include "EventLoop.hpp"
#include "TcpConnection.hpp"
#include <iostream>

using std::cout;
using std::endl;

//连接建立时要做的事儿
void onConnection(wd::TcpConnectionPtr conn)
{
    cout << conn->toString() << " has connected successfully." << endl;
}

//消息到达时要执行的业务逻辑
void onMessage(wd::TcpConnectionPtr conn)
{
    //接收消息
    string msg = conn->receive();
    cout << "recv msg:" << msg << endl;
    //decode
    //compute
    //encode
    //【回显消息】发送消息
    conn->send(msg);
}

//连接断开时要做的事儿
void onClose(wd::TcpConnectionPtr conn)
{
    cout << conn->toString() << " has closed." << endl;
}


void test0()
{
    //结论：可以取地址的表达式是左值；
    //不可以取地址的表达式是右值
    //如果认为onConnection函数名是左值，那就大错特错了
    //所有的普通函数名都是右值，是常量
    //在编译器就确定下来了，后续不能再修改其值,
    //函数名代表的是一个确定的地址值
    //&onConnection;//左值
    //onConnection = 0x100;//error

    //右值引用只能绑定到右值
    int && ref = 1;//ok
    int number = 10;
    number = 100;//ok
    //右值引用不能绑定到左值
    //int && ref2 = number;//error
}

int main()
{
    wd::Acceptor acceptor(8000);
    acceptor.ready();
    printf(">> server start listening.\n");

    wd::EventLoop loop(acceptor);
    loop.setAllCallbacks(onConnection, onMessage, onClose);

    loop.loop();

    return 0;
}

