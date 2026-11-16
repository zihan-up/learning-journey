#include <header.h>

// 代表每一个客户端链接
typedef struct user_t{
    int net_fd; // 为这个客户端单独服务的socket对象文件描述符
    time_t last_time;// 这可客户最后一次说话的时间
}user_msg;

int main(int argc, char *argv[argc]){

    char *port = "8080";
    char *ip = "0.0.0.0";
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
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

    user_msg fds[100];
    memset(fds, 0, sizeof(fds));

    int size = 0; // 记录在数组中有几个链接

    int maxfd = socket_fd;

    fd_set base_set;
    FD_ZERO(&base_set);
    FD_SET(socket_fd, &base_set);

    while(1){
        fd_set set;
        memcpy(&set, &base_set, sizeof(base_set));

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        select(maxfd+1, &set, NULL, NULL, &tv);

        if(FD_ISSET(socket_fd, &set)){
            int net_fd = accept(socket_fd, NULL, NULL);

            FD_SET(net_fd, &base_set);
            maxfd = net_fd >maxfd ? net_fd: maxfd;

            fds[size].net_fd = net_fd;
            time(&fds[size].last_time);// 记录此时此刻的时间
            size++;
        }

        for(int i=0; i<size; i++){
            int net_fd = fds[i].net_fd;
            if(FD_ISSET(net_fd, &set)){
                char buf[100] = {0};
                ssize_t ret = recv(net_fd, buf, sizeof(buf), 0);
                if(ret == 0){
                    close(net_fd);

                    FD_CLR(net_fd, &base_set);

                    for(int k=i; k<size; k++){
                        fds[k] = fds[k+1];
                    }
                    size--;
                    i--;
                    continue;
                }
                // 更新时间
                time(&fds[i].last_time);

                for(int j=0; j<size; j++){
                    if(i != j){
                        send(fds[j].net_fd, buf, sizeof(buf), 0);
                    }
                }
            }
        }

        // 判断所有客户端是不是超时
        for(int i=0; i<size; i++){
            time_t now_time;
            time(&now_time);

            if(now_time - fds[i].last_time > 20){
                // i: 超时-> 踢出: close,  移除监听, 移除记录
                close(fds[i].net_fd);

                FD_CLR(fds[i].net_fd, &base_set);

                for(int k=i; k<size; k++){
                    fds[k] = fds[k+1];
                }
                size--;
                i--;
            }
        }
    }


    // ---------------------------------------------------
    close(socket_fd);
    return 0;
}

