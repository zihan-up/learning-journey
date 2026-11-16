#include <header.h>

int main(int argc, char *argv[argc]){

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);


    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi("9000"));
    sock.sin_addr.s_addr = inet_addr("192.168.106.130");
    connect(socket_fd, (struct sockaddr *)&sock, sizeof(sock));

    int file_fd = open("1.txt", O_RDWR);

    while(1){
        /*
        char buf[4096] = {0};
        size_t ret = read(file_fd, buf, sizeof(buf));
        if(ret == 0){
            break;
        }
        send(socket_fd, buf, ret, 0);
        */

        char buf[4096] = {0};
        ssize_t ret = read(file_fd, buf, sizeof(buf));
        if(ret == 0){
            break;
        }

        send(socket_fd, &ret, sizeof(ret), 0);
        send(socket_fd, buf, ret, 0);


    }


    close(file_fd);
    close(socket_fd);
    return 0;
}

