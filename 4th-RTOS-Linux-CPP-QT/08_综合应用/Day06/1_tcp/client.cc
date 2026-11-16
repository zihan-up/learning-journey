#include <cstdlib>
#include <func.h>
#include <sys/socket.h>


int main()
{
    //1. 创建客户端的套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd < 0) {
        perror("socket");
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

    //2. 连接服务器
    int ret = connect(clientfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if(ret < 0) {
        perror("connect");
        close(clientfd);
        return EXIT_FAILURE;
    }

    //3. 连接成功
    printf("connect success.\n");

#if 0
    //4.发送数据
    const char * hello = "hello,server";
    ret = send(clientfd, hello, strlen(hello), 0);
    printf(">> send %d bytes.\n", ret);
    //5. 接收数据
    char buff[1000] = {0};
    ret = recv(clientfd, buff, sizeof(buff), 0);
    printf(">> recv %d bytes, content:%s\n", ret, buff);
#endif

    while(1);

    close(clientfd);
    return 0;
}

