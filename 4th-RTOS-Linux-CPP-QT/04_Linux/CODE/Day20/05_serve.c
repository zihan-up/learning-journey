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


    while(1){

        char buf[100] = {0};
        // recv: 在TCP连接正常的时候, 默认阻塞函数-> 等待读数据
        // 当recv发现链接断开(四次挥手), recv会从阻塞变成非阻塞
        ssize_t ret = recv(net_fd, buf, sizeof(buf), 0);
        if(ret == 0){
            printf("对方断开链接 \n");
            break;
        }
        printf("buf: %s  \n", buf);

        // -----------------------

        bzero(buf, sizeof(buf));
        read(STDIN_FILENO, buf, sizeof(buf));
        send(net_fd, buf, sizeof(buf), 0);



    }

    close(net_fd);
    close(socket_fd);
    return 0;
}

