#include <header.h>

int main(int argc, char *argv[argc]){

    char *port = "8080";
    char *ip = "0.0.0.0";


    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 如果后续给这个socket对象设置端口的时候
    // 即使端口处于time_wait, 也允许使用
    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    int ret = bind(socket_fd, (struct sockaddr *)&sock, sizeof(sock));
    ERROR_CHECK(ret, -1, "bind");

    listen(socket_fd, 10);

    int net_fd = accept(socket_fd, NULL, NULL);


    fd_set set;
    while(1){
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(net_fd, &set);

        select(net_fd+1, &set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){
            char buf[100] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            send(net_fd, buf, sizeof(buf), 0);
        }
        if(FD_ISSET(net_fd, &set)){
            char buf[100] = {0};
            ssize_t ret = recv(net_fd, buf, sizeof(buf), 0);
            if(ret == 0){
                printf("对方断开链接 \n");
                break;
            }
            printf("buf: %s \n", buf);
        }
    }


    close(net_fd);
    close(socket_fd);
    return 0;
}

