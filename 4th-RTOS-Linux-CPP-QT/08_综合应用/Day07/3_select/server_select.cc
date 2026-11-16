#include <func.h>
#include <sys/select.h>

#define EVENT_ARR_SIZE 100


int main()
{
    //1. 创建服务器的监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }
    printf(">> listenfd is %d.\n", listenfd);

    //1.1设置套接字的属性,网络地址可以重用
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
    ret = listen(listenfd, 20000);
    printf(">> server is listening.\n");

    //maxfd记录当前进程打开的文件描述符的最大值
    int maxfd = listenfd;

    fd_set readfds;//数组，位于栈上
    fd_set monitor_fds;//存储监听的文件描述符
    FD_ZERO(&readfds);
    FD_ZERO(&monitor_fds);
    FD_SET(listenfd, &monitor_fds);

    //事件循环
    while(1) {
        printf("select do wait operation.\n");
        FD_ZERO(&readfds);
        memcpy(&readfds, &monitor_fds, sizeof(fd_set));

        //4. 执行select
        int nready = select(maxfd + 1, &readfds, NULL,NULL,NULL);
        printf("nready: %d\n", nready);
        //当select调用完成之后，readfds中存储的就是已经就绪的文件描述符
        //nready > 0的情况, 有nready个文件描述符就绪了
        //5. 对nready个已经就绪的文件描述符进行相应的处理
        for(int i = 3; i < maxfd + 1; ++i) {
            if(i == listenfd && FD_ISSET(i, &readfds)) {
                //8. 对新连接进行处理
                struct sockaddr_in clientaddr;
                memset(&clientaddr, 0, sizeof(clientaddr));
                socklen_t len = sizeof(clientaddr);
                printf("\nbefore accept.\n");
                //8.0 获取与对端进行交互的netfd(分机)
                int netfd = accept(listenfd, 
                                   (struct sockaddr*)&clientaddr, &len);
                if(netfd < 0) {
                    perror("accept");
                    continue;
                }
                //8.1 打印客户端的网络地址
                printf("\nclient[%d/%s:%d] has connected.\n", netfd,
                       inet_ntoa(clientaddr.sin_addr),
                       ntohs(clientaddr.sin_port));
                //8.2 存储已经建立好的连接netfd,加入到monitor_fds中
                FD_SET(netfd, &monitor_fds);
                //8.3 更新maxfd
                if(maxfd < netfd) {
                    maxfd = netfd;
                }
            } 

            //这是一个已经建立好的连接的处理
            if(i != listenfd && FD_ISSET(i, &readfds)){
                //9. 已经建立好的连接netfd的处理
                char buff[1000] = {0};
                //9.1 从内核接收缓冲区中拷贝数据
                printf(" >>> fd read event trigger.\n");
                ret = recv(i, buff, sizeof(buff), 0);
                if(ret == 0) {
                    printf("\n %d fd has closed.\n", i);
                    FD_CLR(i, &monitor_fds);
                    close(i);//关闭连接
                    continue;
                }
                //9.2 打印接收的数据到终端上
                printf("\n>> recv %d bytes, msg: %s\n", ret, buff);
                //9.3 进行业务逻辑的处理[回显echo]
                ret = send(i, buff, strlen(buff), 0);
                printf("\n>> send %d bytes.\n", ret);
            }
        }
    }//end of while

    return 0;
}

