#include <header.h>

int main(int argc, char *argv[argc]){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in  sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    connect(socket_fd, (struct sockaddr *)&sock, sizeof(sock));

    int flag = 0;
    fd_set set;
    while(1){
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        if(flag == 0){
            FD_SET(socket_fd, &set);
        }

        select(socket_fd+1, &set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){

            if(flag == -1){
                socket_fd = socket(AF_INET, SOCK_STREAM, 0);
                connect(socket_fd, (struct sockaddr *)&sock, sizeof(sock));
                flag = 0;
            }

            char buf[100] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            send(socket_fd, buf, sizeof(buf), 0);
        }
        if(FD_ISSET(socket_fd, &set)){
            char buf[100] = {0};
            ssize_t ret = recv(socket_fd, buf, sizeof(buf), 0);
            if(ret == 0){
                printf("对方断开链接 \n");

                flag = -1;
                continue;
            }
            printf("buf: %s \n", buf);
        }
    }

    close(socket_fd);
    return 0;
}

