#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    wd::Acceptor acceptor(8000);
    acceptor.ready();
    printf(">> server start listening.\n");

    int netfd = acceptor.accept();
    wd::TcpConnection conn(netfd);
    cout << conn.toString() << " has connected successfully." << endl;

    conn.send("welcome to server.");
    cout << "receive msg: " << conn.receive() << endl;


    return 0;
}

