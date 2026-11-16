#include <header.h>

void a(int num){
    if(num == 0){
        return ;
    }

    num--;

    a(num);
}

int main(int argc, char *argv[argc]){

    int num = 10000000;
    a(num);

    return 0;
}

