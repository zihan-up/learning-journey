#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include <iostream>
#include <sys/socket.h>


using std::cout;
using std::endl;

int main()
{
    wd::Acceptor acceptor(8000);
    acceptor.ready();

    cout << "server start listening" << endl;

    //当没有客户端进行交互时，程序就阻塞在accept方法之上了
    wd::TcpConnection conn(acceptor.accept());
    cout << conn.toString() << " has connected" << endl;

    string msg = conn.receive();
    cout << "server recv:" << msg << endl;
    conn.send(msg);

    return 0;
}

