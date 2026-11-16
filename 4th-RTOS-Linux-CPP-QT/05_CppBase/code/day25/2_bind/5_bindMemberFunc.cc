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
public:
    //int data() {return 100;}
    int data = 100;//C++11中可以在声明数据成员的时候直接初始化
};

void test()
{
    Example ex;
    function<int()> f = bind(&Example::add, &ex, 10, 20);
    cout << "f() = " << f() << endl;

    cout << endl;
    function<int()> f2 = bind(&Example::data, &ex);
    cout << "f2() = " << f2() << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

