#ifndef __EchoServer_H__
#define __EchoServer_H__

#include "TcpConnection.hpp"
#include "Threadpool.hpp"
#include "TcpServer.hpp"

using namespace wd;

class EchoServer
{
public:
    EchoServer(unsigned short port, const string & ip, int, int);

    void start();
    void stop();

    void onConnection(TcpConnectionPtr conn);
    void onMessage(TcpConnectionPtr conn);
    void onClose(TcpConnectionPtr conn);

private:
    Threadpool _threadpool;
    TcpServer  _tcpServer;

};

#endif

