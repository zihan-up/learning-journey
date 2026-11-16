#include <func.h>

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
    //C10K的问题
    ret = listen(listenfd, 20000);
    printf(">> server is listening.\n");


    //4. 创建epoll的实例
    int epfd = epoll_create1(0);
    if(epfd < 0) {
        perror("epoll_create1");
        return EXIT_FAILURE;
    }
    printf(">> epfd is %d.\n", epfd);


    //5. 监听listenfd上的读事件
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    if(ret < 0) {
        perror("epoll_ctl");
        return EXIT_FAILURE;
    }
    //6. 准备用户态中存储已经就绪的文件描述符及其事件
    struct epoll_event evtArr[EVENT_ARR_SIZE] = {0};

    while(1) {
        int nready = epoll_wait(epfd, evtArr, EVENT_ARR_SIZE, 5000);
        if(nready == -1 && errno == EINTR) {
            continue;
        } else if(nready == 0) {
            //注意：当从上一次超时或有fd就绪 到下一次超时之间的5秒钟内，
            //如果有文件描述符就绪，就不会再执行超时的分支;
            //只有5秒以内没有任何文件描述符就绪时，才会执行超时的分支
            printf("\nepoll timeout.\n");
        } else if(nready == -1) {
            perror("epoll_wait");
            return EXIT_FAILURE;
        } else {
            //nready > 0的情况, 有nready个文件描述符就绪了
            //7. 对nready个已经就绪的文件描述符进行相应的处理
            for(int i = 0; i < nready; ++i) {
                int fd = evtArr[i].data.fd;
                if(fd == listenfd) {
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
                    //8.2 由epoll对netfd的读事件进行监听
                    ev.data.fd = netfd;
                    ev.events = EPOLLIN;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &ev);
                } else {
                    //9. 已经建立好的连接的处理
                    char buff[1000] = {0};
                    //9.1 从内核接收缓冲区中拷贝数据
                    ret = recv(fd, buff, sizeof(buff), 0);
                    //当连接断开时，一定会触发读事件
                    if(ret == 0) {
                        printf("\n %d fd has closed.\n", fd);
                        //先从epoll的监听红黑树上删除fd
                        ev.data.fd = fd;
                        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
                        close(fd);//关闭连接
                        continue;
                    }

                    //9.2 打印接收的数据到终端上
                    printf("\n>> recv %d bytes, msg: %s\n", ret, buff);
                    //9.3 进行业务逻辑的处理[回显echo]
                    //对于数组，发送消息时，不能用sizeof获取长度，
                    //这样会直接把这个数组的数据发送给对端的
                    //而其中很有可能有大量的无效的数据0
                    ret = send(fd, buff, strlen(buff), 0);
                    printf("\n>> send %d bytes.\n", ret);
                }
            }
        }


    }//end of while

    return 0;
}

