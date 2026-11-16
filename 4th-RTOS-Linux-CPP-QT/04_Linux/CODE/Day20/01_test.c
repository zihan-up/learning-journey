#include <header.h>

int main(int argc, char *argv[argc]){
    // int 4字节, 字节位从高到底分别为:  0x75,  0x76, 0x77, 0x78
    // 因为主机采用小端法, 低字节/低位  -> 低地址
    // 所以: 按照地址从低到高, 依次存储: 0x78, 0x77, 0x76, 0x75 
    int num = 0x7576777A;

    // u v  w  x
    // 75  76   77   78
    num = htonl(num);

    // &num: 取地址, 取的是首地址/低地址, 即0x78的地址
    // 把存储了0x78的地址, 用*c保存, *c指向了0x78
    char *c = (char *) &num;
    // 打印0x78, 按照字符打印;  我们知道0x78 对应的二进制为0111 1000 十进制即120,   而字符x所对应的ascii码值为120, 所以打印x
    printf("the first char : %c \n", *c);


    return 0;
}

