#include <header.h>

int main(int argc, char *argv[argc]){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);


    struct sockaddr_in  sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    // -----------------------------------

    fd_set set;
    while(1){
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(socket_fd, &set);

        select(10, &set,NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){
            char buf[100] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            sendto(socket_fd, buf, sizeof(buf), 0,   (struct sockaddr *)&sock, sizeof(sock));
        }

        if(FD_ISSET(socket_fd, &set)){
            char buf[100] = {0};
            recvfrom(socket_fd, buf, sizeof(buf), 0, 
                     NULL, NULL);
            printf("buf: %s \n", buf);
        }
    }

    // -----------------------------------
    close(socket_fd);
    return 0;
}

