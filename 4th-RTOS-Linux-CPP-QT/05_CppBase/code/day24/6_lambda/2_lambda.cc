#include <iostream>

using std::cout;
using std::endl;

void test()
{
    //lambda表达式的完整形式
    int number = 1;
    [number](int value)mutable->void{
        cout << "value = " << value <<endl;
        cout << "number = " << number << endl;
    }(100);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

