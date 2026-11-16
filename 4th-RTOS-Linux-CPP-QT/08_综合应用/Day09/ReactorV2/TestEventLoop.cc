#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include "EventLoop.hpp"
#include <iostream>

using std::cout;
using std::endl;


void onConnection(wd::TcpConnectionPtr conn)
{
    cout << conn->toString() << " has connected successfully.\n";
}

void onMessage(wd::TcpConnectionPtr conn)
{
    //read
    string msg = conn->receive();
    cout << "recv: " << msg << endl;

    //decode
    //compute
    //encode
    
    //假设执行的回显服务
    string response = msg;
    //send
    conn->send(response);
}

void onClose(wd::TcpConnectionPtr conn)
{
    cout << conn->toString() << " has closed." << endl;
}


int main()
{
    wd::Acceptor acceptor(8000);
    acceptor.ready();

    wd::EventLoop loop(acceptor);
    loop.setAllCallbacks(onConnection, 
                         onMessage,
                         onClose);
    
    loop.loop();

    return 0;
}

