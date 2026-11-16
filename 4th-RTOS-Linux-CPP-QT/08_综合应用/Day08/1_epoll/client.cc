#include <cstdlib>
#include <func.h>
#include <sys/socket.h>
#include <unistd.h>


int main()
{
    //1. 创建客户端的套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }
    printf("clientfd: %d\n", clientfd);

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

    //4. 使用select进行监听: 标准输入, clientfd
    fd_set readfds;
    
    char buff[1000] = {0};

    while(1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(clientfd, &readfds);
        //select是一个阻塞式函数
        int ret = select(clientfd + 1, &readfds, NULL, NULL, NULL);
        printf(">> %d fd ready.\n", ret);

        //判断标准输入和clientfd上是否有读事件发生
        if(FD_ISSET(STDIN_FILENO, &readfds)) {
            memset(buff, 0, sizeof(buff));
            ret = read(STDIN_FILENO, buff, sizeof(buff));
            printf("\nread %d bytes from stdin.\n", ret);

            //发送给服务器
            ret = send(clientfd, buff, strlen(buff), 0);
            printf("\nsend %d bytes.\n", ret);
        }

        if(FD_ISSET(clientfd, &readfds)) {
            memset(buff, 0, sizeof(buff));
            //服务器发送数据过来了
            ret = recv(clientfd, buff, sizeof(buff), 0);
            if(ret == 0) {
                printf("\nserver closed.\n");
                close(clientfd);
                break;
            }
            printf("\n recv %d bytes, msg:%s\n", ret, buff);
        }
    }

    close(clientfd);
    return 0;
}

