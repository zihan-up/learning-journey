#include <iostream>

using std::cout;
using std::endl;

//class与struct的区别
//1、默认访问权限不一样，struct是public，class是private
//2、默认的继承方式不一样，struct默认继承方式是public的，
//但是class默认继承方式是private
/* class Base */
struct Base
{
public:
    void print()
    {
        cout << "void Base::print()" << endl;
    }
};

/* class Derived */
struct Derived
: Base
{

};

void test()
{
    Derived d;
    d.print();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

