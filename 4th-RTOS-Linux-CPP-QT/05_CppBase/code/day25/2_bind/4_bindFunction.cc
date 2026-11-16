#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;
using std::function;

int add(int x, int y)
{
    cout << "int add(int, int)" << endl;
    return x + y;
}

int multiply(int x, int y, int z)
{
    cout << "int multiply(int, int, int)" << endl;
    return x * y * z;
}

class Example
{
public:
    int add(int x, int y)
    {
        cout << "int Example::add(int, int)" << endl;
        return x + y;
    }
};

void test()
{
    //函数的类型（形态、标签）:函数的返回类型与
    //函数的参数列表（参数的个数、顺序、类型）
    //add函数的类型：int(int, int)
    //通过bind绑定add函数之后的f的形态：int()
    /* auto f = bind(&add, 1, 2); */
    //function是函数的容器，因为可以存放函数类型
    function<int()> f = bind(&add, 1, 2);
    cout << "f() = " << f() << endl;

    cout << endl;
    //multiply函数的类型：int(int, int, int)
    //通过bind绑定multiply函数之后的f2的形态：int()
    function<int()> f2 = bind(&multiply, 3, 4, 5);
    cout << "f2() = " << f2() << endl;

    cout << endl;
    Example ex;
    //成员函数add的形态：int(Example *, int, int)
    //通过bind绑定成员函数add之后的f3的形态：int()
    function<int()> f3 = bind(&Example::add, &ex, 10, 20);
    cout << "f3() = " << f3() << endl;

    cout << endl;
    //add函数的类型：int(int, int)
    //通过bind绑定函数add之后的f4的形态：int(int)
    function<int(int)> f4 = bind(&add, 11, std::placeholders::_1);
    cout << "f4(33) = " << f4(33) << endl;

    cout << endl;
    //add函数的类型：int(int, int)
    //通过bind绑定函数add之后的f5的形态：int(int, int)
    using namespace std::placeholders;
    function<int(int, int)> f5 = bind(&add, _1, _2);
    cout << "f5(77, 22) = " << f5(77, 22) << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

