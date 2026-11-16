#include "EchoServer.hpp"
#include "BussinessService.hpp"
#include <iostream>

using std::cout;
using std::endl;


EchoServer::EchoServer(unsigned short port, const string & ip, int threadNum, int sz)
: _threadpool(threadNum, sz) 
, _tcpServer(port, ip)
{
    using namespace std::placeholders;
    _tcpServer.setAllCallbacks(
        std::bind(&EchoServer::onConnection, this, _1),
        std::bind(&EchoServer::onMessage, this, _1),
        std::bind(&EchoServer::onClose, this, _1));
}

void EchoServer::start()
{
    _threadpool.start();
    _tcpServer.start();
}

void EchoServer::stop()
{
    _tcpServer.stop();
    _threadpool.stop();
}

void EchoServer::onConnection(TcpConnectionPtr conn)
{
    cout << "\nio thread " << pthread_self() 
         << ": ReactorV5: " << conn->toString() << " has connected successfully." << endl;
}

void EchoServer::onMessage(TcpConnectionPtr conn)
{
    //接收消息
    string msg = conn->receive();
    cout << "\nio thread " << pthread_self() 
         << ": ReactorV5 recv msg:" << msg << endl;
    //将消息封装成一个任务，交给线程池执行
    Mytask mytask(msg, conn);
    _threadpool.addTask(std::bind(&Mytask::process, mytask));
}

void EchoServer::onClose(TcpConnectionPtr conn)
{
    cout << "\nio thread " << pthread_self() 
         << ": ReactorV5: " << conn->toString() << " has connected successfully." << endl;
}

