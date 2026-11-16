#include <header.h>

int main()
{
    char *port = "9000";
    char *ip = "0.0.0.0";
    //char *ip = "192.168.106.130";
    //char *ip = "127.0.0.0";


    // socket函数: 创建socket端点对象(内核中)
    // 在这个socket对象, 有输出缓冲区, 和输入缓冲区
    // 输出缓冲区:  当有数据要发送到网络上, 可以把用户态的数据拷贝到输出缓冲
    //               (操作系统会选择合适的时机, 把数据拷贝到网卡上, 网卡把数据发送网络)
    // 输入缓冲区:  当网络数据到来, 操作系统收到一份数据(网卡接收交给操作系统), 会检查数据给谁的(给那个socket的: 比如端口)
    //              比如操作系统会检查收到的数据信息, 检查信息给那个端口的, 进一步把数据转给和对应对应端口关联的socket对象
    //              等待用户程序读取输入缓冲区(把数据读走)
    // socket执行结束的时候, 还会把socket对象地址/引用/指针信息  , 放到文件描述符数组中
    // 返回下标(文件描述符数组的下标)
    // 参数1:通知socket: 使用IPv4 -> AF_INET 
    // 参数2:通知socket: 使用TCP协议 -> SOCK_STREAM
    // 参数3: 进一步指明协议:  0 -> 要求底层自动填充
    // 返回值: 是一个文件描述符数组的下标
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 此时此刻: socket对象和端口无关

    struct  sockaddr_in  sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    // 给某个socket对象绑定端口 和  ip信息
    // 参数1: (文件描述符数组下标)给那个socket对象去设置  端口和ip
    // 参数2: 绑定的 端口  和  IP信息   (通用类型: IPv4 IPv6类型的结构体 -> 结构体强转)
    // 参数3: 告诉bind函数, (作为一个类似flag标记位存在) , 传入同类类型的结构体, 本质是什么类型 (通过结构体大小的方式告诉)
    // 返回值: 绑定成功或者失败
    // 注: bind绑定的是服务器的端口, 用来让socket对象去"监听"这个端口.等待接收向这个端口发送的数据
    // 注: bind绑定的IP地址, 也是服务器自己的
    int ret = bind(socket_fd, (struct sockaddr *)&sock, sizeof(sock));
    ERROR_CHECK(ret, -1, "bind");
    


    // listen: 要求socket对象放弃对输入输出缓冲区的持有, 创建半连接队列  和  全链接队列
    // 半链接队列是为了存储握手完成一半信息 (第一次第二次握手)
    // 全连接队列是为了存储三次握手已经完毕的信息
    // 参数1: 要求那个socket对象做如上改变
    // 参数2: 队列的长度
    listen(socket_fd, 10);

   // 可以接受三次握手 

    printf("---- \n");
    // accept: 从全连接队列中, 获取已经三次握手完毕的信息, 获取一个新的socket对象, 
    //         把这个对象的引用存储在文件描述符数组中, 获得文件描述符数组的下标
    // 注: accept有可能阻塞-> 当全连接队列中无信息(没有那个客户端来三次握手), 阻塞
    //                     -> 当三次握手完毕, 全连接队列中有内容 -> 解除阻塞
    // 注: 这个accept获得的新的socket对象, 是专门用来服务这个一个客户端的(从全连接队列拿出握手信息的代表客户端)
    //
    // 参数1: 去那个socket对象中检查全连接队列, 获取信息 
    // 参数2: 当accept获得了一个新的链接信息, 这个链接信息, 来自那个客户端的端口和IP, 可以用这个参数接收
    // 参数3: ipv4 ipv6类型
    // 返回值: 新的socket对象的文件描述符下标 

    struct sockaddr_in sock_client;
    socklen_t len = sizeof(sock_client);
    //int net_fd = accept(socket_fd, (struct sockaddr *)&sock, &len);
    int net_fd = accept(socket_fd, NULL, NULL);
    printf("****** \n");


    // send 和 recv: (其实底层本质就是write    read), 
    //  但是send和recv是专门给收发网络数据用的, 用来和socket进行交互
    // 注:  send 和 recv 仅仅只是把数据从内核和输入输出缓冲区  和用户态进行拷贝
    //      数据什么时候到来, 或者数据什么时候从输出缓冲区拷贝到网卡, send 和recv决定不了, 操作自行决定


    char buf[100] = {0};
    recv(net_fd, buf, sizeof(buf), 0);
    printf("buf: %s \n", buf);

    send(net_fd, "nihao", 5, 0);

    close(net_fd);
    close(socket_fd);





    return 0;
}

