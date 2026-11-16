#include <header.h>

int main(){

    int fd = open("2.txt", O_RDWR|O_CREAT, 0666);

    return 0;
}

