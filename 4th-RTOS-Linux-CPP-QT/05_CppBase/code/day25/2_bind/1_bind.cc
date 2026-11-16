#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

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
    auto f = bind(&add, 1, 2);
    cout << "f() = " << f() << endl;

    cout << endl;
    auto f2 = bind(&multiply, 3, 4, 5);
    cout << "f2() = " << f2() << endl;

    cout << endl;
    Example ex;
    auto f3 = bind(&Example::add, &ex, 10, 20);
    cout << "f3() = " << f3() << endl;

    cout << endl;
    //占位符
    auto f4 = bind(&add, 11, std::placeholders::_1);
    cout << "f4(22) = " << f4(22) << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

