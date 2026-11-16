#include "line.h"
#include <iostream>
using std::cout;
using std::endl;

void test(){
    Line line(1, 2, 3, 4);
    line.printLine();
}

int main()
{
    test();
    return 0;
}

