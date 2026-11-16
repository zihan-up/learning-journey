#include <header.h>


size_t my_recv(int net_fd, char *buf, size_t len){

    // 记录读到的数据字节个数
    size_t index = 0;

    // 只要没有读够数据, 一直读取
    while(index < len){

        // 缺多少:读多少:  len-index 
        ssize_t ret = recv(net_fd, buf+index, len-index, 0);
        if(ret == 0){
            break;
        }
        index += ret;
    }

    return  index;
}
int main()
{
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

    int file_fd = open("1.txt", O_RDWR|O_CREAT, 0666);

    while(1){
        /*
        char buf[4096]= {0};
        ssize_t ret = recv(net_fd, buf, sizeof(buf), 0);
        if(ret == 0){
            break;
        }
        write(file_fd, buf, ret);
        */

        ssize_t len = 0;
        ssize_t ret = recv(net_fd, &len, sizeof(ssize_t), 0);
        if(len != 4096)
        printf("len: %ld \n", len);
        if(ret == 0){
            break;
        }
        char buf[4096]= {0};
        //ret = recv(net_fd, buf, len, 0);
        //ret = my_recv(net_fd, buf, len);
        ret = recv(net_fd, buf, len, MSG_WAITALL);
        if(ret == 0){
            break;
        }
        write(file_fd, buf, ret);

    }


    close(file_fd);
    close(net_fd);
    close(socket_fd);
    return 0;
}

