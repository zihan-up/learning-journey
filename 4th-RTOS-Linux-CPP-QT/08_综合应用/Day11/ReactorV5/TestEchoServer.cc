#include "EchoServer.hpp"
#include <iostream>

using std::cout;
using std::endl;


int main()
{
    EchoServer server(8000, "127.0.0.1", 4, 10);
    cout << ">> server start listening." << endl;

    //服务器开始事件循环
    server.start();

    return 0;
}

