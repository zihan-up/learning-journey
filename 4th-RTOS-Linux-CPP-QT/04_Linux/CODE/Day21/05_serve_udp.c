#include <header.h>

int main(int argc, char *argv[argc]){

    char *ip = "0.0.0.0";
    char *port = "8080";

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    bind(socket_fd, (struct sockaddr *)&sock, sizeof(sock));

    // -----------------------
    //
    struct sockaddr_in sock_client;
    socklen_t len = sizeof(sock_client);

    char buf[100] = {0};
    recvfrom(socket_fd, buf, sizeof(buf), 0, 
             (struct sockaddr *)&sock_client, &len);

    printf("buf: %s \n", buf);

    sendto(socket_fd, "hello", 5, 0, 
           (struct sockaddr *)&sock_client, sizeof(sock_client));

    // ----------------------
    close(socket_fd);
    return 0;
}

