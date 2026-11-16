#include "logger.h"
#include <iostream>
using std::cout;
using std::endl;

void test(){
    LOG_WARN("this is a warn message");
}

void test2(){
    LOG_INFO("this is a info message");
}

int main()
{
    test();
    test2();
    return 0;
}

