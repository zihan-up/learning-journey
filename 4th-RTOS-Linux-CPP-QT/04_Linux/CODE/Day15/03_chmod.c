#include <header.h>

int main(int argc, char *argv[argc]){

    // 相对路径  和 绝对路径
    //chmod("./1.txt", 0666);
    //chmod("/home/snow/code/4th/04_Linux/CODE/Day15/1.txt", 0666);

    int ret = chmod("1.txt", 0666);
    ERROR_CHECK(ret, -1, "chmod");

    ret = chmod("test", 0777);
    ERROR_CHECK(ret, -1, "chmod");

    return 0;
}

