#include <iostream>

using std::cout;
using std::endl;

int add(int x, int y)
{
    cout << "int add(int, int)" <<endl;
    return x + y;
}

class Example
{
public:
    int func(int x, int y)
    {
        cout << "int func(int, int)" <<endl;
        return x + y;
    }

};

void test()
{
    int (*pFunc)(int, int);//普通的函数指针
    pFunc = add;
    cout << "pFunc(3, 4) = " << pFunc(3, 4) << endl;

    cout << endl;
    int (Example::*pFuncA)(int, int);//成员函数指针
    pFuncA = &Example::func;
    Example ex;
    cout << (ex.*pFuncA)(4, 5) << endl;

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

