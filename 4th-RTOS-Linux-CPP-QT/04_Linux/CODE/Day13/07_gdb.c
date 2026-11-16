#include <header.h>

void c(){
    int num = 10;
    printf("num:%d \n", num);
}

void b(){
    c();
}
void a(){
    b();
}

int main(int argc, char *argv[argc]){

    a();

    return 0;
}

