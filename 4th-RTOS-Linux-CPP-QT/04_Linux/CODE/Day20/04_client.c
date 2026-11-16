#include <header.h>

int main(int argc, char *argv[argc]){

    char *port = "9000";
    //char *ip = "47.115.220.165";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in  sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);


    // connect: 主动向服务器发起三次握手
    // 参数1: 使用那个socket对象, 向服务器发起握手
    // 参数2: 需要设置服务器的端口和ip, 用于向这个服务器发起三次握手
    // 参数3: 结构体大小 (ipv6, ipv4)
    int ret = connect(socket_fd, (struct sockaddr *)&sock, sizeof(sock));
    ERROR_CHECK(ret, -1, "connect");
    // 当connect结束, 程序走到这个位置 : 表示三次握手结束了( 要么握手成功, 要么握手失败 )

    while(1){

    }

    send(socket_fd, "zaima", 5, 0);

    char buf[100] = {0};
    recv(socket_fd, buf, sizeof(buf), 0);
    printf("buf: %s \n", buf);



    close(socket_fd);

    return 0;
}

