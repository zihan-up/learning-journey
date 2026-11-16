#include <arpa/inet.h>
#include <cstdlib>
#include <func.h>
#include <sys/socket.h>


int main()
{
    //1. 创建服务器的监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    //设置套接字的属性,网络地址可以重用
    int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(ret < 0) {
        perror("setsockopt");
        close(listenfd);
        return EXIT_FAILURE;
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8000);
    //127.0.0.1  代表的是本地环回地址
    //客户端要连接服务器，只能在本机上操作,抓包一般是抓不到的
    //
    //0.0.0.0  代表的是本机地址，客户端可以在远程连接服务器
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //2. 绑定网络地址
    ret = bind(listenfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if(ret < 0) {
        perror("bind");
        close(listenfd);
        return EXIT_FAILURE;
    }

    //3. 服务器进行监听
    //C10K的问题
    ret = listen(listenfd, 20000);

    while(1) {
        struct sockaddr_in clientaddr;
        memset(&clientaddr, 0, sizeof(clientaddr));
        socklen_t len = sizeof(clientaddr);
        printf("\nbefore accept.\n");
        //4. 从内核的全连接队列上去下一个已经建立好的连接
        //默认情况下也是一个阻塞式的函数
        //Q1:客户端（新连接）到来的时机不确定
        int netfd = accept(listenfd, 
                           (struct sockaddr*)&clientaddr, &len);
        if(netfd < 0) {
            perror("accept");
            continue;
        }
        //5. 打印客户端的网络地址
        printf("client[%s:%d] has connected.\n",
               inet_ntoa(clientaddr.sin_addr),
               ntohs(clientaddr.sin_port));

        //6. 进行数据的接收和发送
        char buff[1000] = {0};
        //recv函数默认情况下是一个阻塞式函数
        //Q2: 客户端发送数据的时机不确定的,服务器
        //接收数据的时机也变得不确定的
        ret = recv(netfd, buff, sizeof(buff), 0);
        printf(">> recv %d bytes, content:%s\n", ret, buff);

        const char * hello = "hello, client";
        ret = send(netfd, hello, strlen(hello), 0);
        close(netfd);
    }

    return 0;
}

