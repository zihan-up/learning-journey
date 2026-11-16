#include <header.h>

int main(int argc, char *argv[argc]){

    char *port = "8080";
    char *ip = "192.168.106.130";

    // 构建出一个socket函数需要的结构体: 这个结构体中存储了IP和端口
    // 后续我们使用socket的相关函数的时候, 直接把这个结构体传给socket的相关函数, 用来指明IP和端口

    struct sockaddr_in sock; // IPv4
    sock.sin_family = AF_INET; // 代表IPv4
    sock.sin_port = htons(atoi(port));// 大端的端口
    sock.sin_addr.s_addr = inet_addr(ip);// 大端的IP地址

    // 一些socket的函数需要端口和ip
    bind(10,   (struct sockaddr *)&sock,  sizeof(sock));

    return 0;
}

