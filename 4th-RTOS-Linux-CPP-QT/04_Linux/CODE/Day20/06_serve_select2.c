#include <header.h>

int main(int argc, char *argv[argc]){

    char *port = "9000";
    char *ip = "0.0.0.0";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    bind(socket_fd, (struct sockaddr *)&sock, sizeof(sock));

    listen(socket_fd, 10);

    int net_fd = accept(socket_fd, NULL, NULL);
    printf("有客户端链接过来 \n");



    fd_set set;

    while(1){
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(net_fd, &set);

        select(net_fd+1, &set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){
            // 说明select监听完毕(从内核回到用户态), 发现标准输入可读:  读标准输入->给对方发信息
            char buf[100] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            send(net_fd, buf, sizeof(buf), 0);
        }
        if(FD_ISSET(net_fd, &set)){
            // 说明select监听完毕(从内核回到用户态), 发现socket对象变得可读:  读socket对象->打印
            char buf[100] = {0};
            ssize_t ret = recv(net_fd, buf, sizeof(buf), 0);
            if(ret == 0){
                printf("对方断开链接 \n");
                break;
            }
            printf("buf: %s  \n", buf);
        }
    }

    close(net_fd);
    close(socket_fd);
    return 0;
}

