#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;
using std::function;

class Example
{
public:
    int add(int x, int y)
    {
        cout << "int Example::add(int, int)" << endl;
        return x + y;
    }
};

int func()
{
    return 10;
}

void test()
{
    int a = 10;
    int (*pFunc)() = func;//ok,函数指针
    int (&pFunc2)() = func;//ok，函数引用

    Example ex;
    function<int()> f = bind(&Example::add, &ex, 10, 20);
    cout << "f() = " << f() << endl;

    cout << endl;
    function<int()> f1 = bind(&Example::add, ex, 10, 20);
    cout << "f1() = " << f1() << endl;

    cout << endl;
    using namespace std::placeholders;
    auto f2 = bind(&Example::add, _1, 100, 900);
    cout << "f2(&ex) = " << f2(&ex) << endl;
    cout << "f2(ex) = " << f2(ex) << endl;

    cout << endl;
    function<int(Example *)> f3 = bind(&Example::add, _1, 20, 30);
    cout << "f3(&ex) = " << f3(&ex) << endl;

    cout << endl;
    function<int(Example &)> f4 = bind(&Example::add, _1, 4, 6);
    cout << "f4(ex) = " << f4(ex) << endl;

    cout << endl;
    function<int(Example )> f5 = bind(&Example::add, _1, 11, 33);
    cout << "f5(ex) = " << f5(ex) << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

