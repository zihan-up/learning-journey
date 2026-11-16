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
    // ---------------------------------------------------
    // 1, 新链接获取监听保存
    // 2, 某个链接发信息过来

    // 保存所有的客户端链接
    int fds[100] = {0};
    int size = 0; // 记录在数组中有几个链接

    int maxfd = socket_fd;

    fd_set set;
    while(1){
        FD_ZERO(&set);
        FD_SET(socket_fd, &set);

        for(int i=0; i<size; i++){
            FD_SET(fds[i], &set);
        }

        select(maxfd+1, &set, NULL, NULL, NULL);

        if(FD_ISSET(socket_fd, &set)){
            // 有新的客户端过来:  获取新链接, 放入监听, 保存记录
            int net_fd = accept(socket_fd, NULL, NULL);
            
            fds[size] = net_fd;
            size++;
        }




    }


    // ---------------------------------------------------
    close(socket_fd);
    return 0;
}

