#include <header.h>


int main(int argc, char *argv[argc]){

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);


    // 硬编码
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi("9000"));
    sock.sin_addr.s_addr = inet_addr("47.115.220.165");
    connect(socket_fd, (struct sockaddr *)&sock, sizeof(sock));

   
    char *file_name = "1.txt";

    size_t file_name_len = strlen(file_name);

    send(socket_fd, &file_name_len, sizeof(size_t), 0);

    // file_name, file_size, txt 
    send(socket_fd, file_name, file_name_len, 0);


    struct stat st;
    stat(file_name, &st);
    send(socket_fd, &st.st_size, sizeof(off_t), 0);

    int file_fd = open(file_name, O_RDWR);
    char buf[4096] = {0};
    ssize_t ret = read(file_fd, buf, sizeof(buf));
    send(socket_fd, buf, st.st_size, 0);


    close(socket_fd);
    return 0;
}

