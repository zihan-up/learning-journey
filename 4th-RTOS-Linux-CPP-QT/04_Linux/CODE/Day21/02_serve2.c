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

    // 保存下一次要监听的所有的socket对象
    fd_set base_set;
    FD_ZERO(&base_set);
    FD_SET(socket_fd, &base_set);

    while(1){
        // 保存本次监听需要的对象下标
        fd_set set;
        memcpy(&set, &base_set, sizeof(base_set));

        select(maxfd+1, &set, NULL, NULL, NULL);

        if(FD_ISSET(socket_fd, &set)){
            // 有新的客户端过来:  获取新链接, 放入监听, 保存记录
            int net_fd = accept(socket_fd, NULL, NULL);

            FD_SET(net_fd, &base_set);
            maxfd = net_fd >maxfd ? net_fd: maxfd;

            fds[size] = net_fd;
            size++;
        }

        // 判断没有没有那个客户端发信息过来
        for(int i=0; i<size; i++){
            int net_fd = fds[i];
            if(FD_ISSET(net_fd, &set)){
                // 说明这个客户端发送信息过来
                char buf[100] = {0};
                ssize_t ret = recv(net_fd, buf, sizeof(buf), 0);
                if(ret == 0){
                    // 这个客户端可读, 但是没有读到数据  -> 这个客户端断开链接
                    // close, 移除监听, 移除fds记录
                    close(net_fd);

                    FD_CLR(net_fd, &base_set);

                    for(int k=i; k<size; k++){
                        fds[k] = fds[k+1];
                    }
                    size--;
                    i--;
                    continue;
                }

                // 转发: 发给除自己以外的所有人
                for(int j=0; j<size; j++){
                    if(i != j){
                        // 只要不是我自己, 就转发
                        send(fds[j], buf, sizeof(buf), 0);
                    }
                }
            }
        }
    }


    // ---------------------------------------------------
    close(socket_fd);
    return 0;
}

