#include <iostream>

using std::cout;
using std::endl;

int func()
{
    cout <<"int func()" << endl;
    return 10;
}

int func2()
{
    cout <<"int func2()" << endl;
    return 20;
}

int add(int x, int y)
{
    cout << "int add(int, int)" << endl;
    return x + y;
}

void test()
{
    //1、定义函数指针
    typedef int(*pFunc)();
    /* typedef int(*)() pFunc;//error */
    /* using pFunc2 = int(*)();//C++中的写法 */

    //2、延迟调用的思想(C++中的多态就是这一种思想，可以提高代码的灵活性)
    //
    //3、回调函数的使用步骤：注册回调函数、执行回调函数
    pFunc f = func;//回调函数的注册（交给函数指针）
    cout << "f() = " << f() << endl;//执行回调函数（函数指针的执行间接激发了
                                    //回调函数的执行）
    cout <<endl;
    f = func2;
    cout << "f() = " << f() << endl;

    /* f = add; */
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

