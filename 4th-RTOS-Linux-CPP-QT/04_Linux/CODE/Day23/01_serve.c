#include <header.h>


int flag = 3;

void my_write(char *str,  int tag){
    if(tag > flag ){

        //write(str);
    }
}

int main()
{
    char *port = "9000";
    char *ip = "0.0.0.0";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd  == -1){
        // 写日志: 创建socket对象失败, 错误
        my_wirte("socket create 失败", 3);
    } 

    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    bind(socket_fd, (struct sockaddr *)&sock, sizeof(sock));
    listen(socket_fd, 10);


    int net_fd = accept(socket_fd, NULL, NULL);
    // 写日志: 新链接进来
    my_wirte("新链接进来", 1);

    size_t file_name_len = 0;
    recv(net_fd, &file_name_len, sizeof(size_t), 0);



    char file_name[256] = {0};
    ssize_t ret = recv(net_fd, file_name, file_name_len, 0);
    printf("ret: %ld \n", ret);



    off_t file_size = 0;
    recv(net_fd, &file_size, sizeof(off_t), 0);



    char buf[4096] = {0};
    recv(net_fd, buf, file_size, 0);


    // 
    printf("file_name: %s \n", file_name);
    printf("file_size: %ld \n", file_size);
    printf("buf: %s \n", buf);



    close(net_fd);
    close(socket_fd);
    return 0;
}

