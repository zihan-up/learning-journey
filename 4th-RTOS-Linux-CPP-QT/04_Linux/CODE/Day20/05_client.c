#include <header.h>

int main(int argc, char *argv[argc]){

    char *port = "9000";
    char *ip = "192.168.106.130";


    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);


    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    connect(socket_fd, (struct sockaddr *)&sock, sizeof(sock));

    

    while(1){

        char buf[100] = {0};
        read(STDIN_FILENO, buf, sizeof(buf));
        send(socket_fd, buf, sizeof(buf), 0);
        // -----------------------

        memset(buf, 0, sizeof(buf));
        ssize_t ret = recv(socket_fd, buf, sizeof(buf), 0);
        if(ret == 0){
            printf("对方断开链接  \n");
            break;
        }
        printf("buf: %s \n", buf);


    }

    close(socket_fd);
    return 0;
}

