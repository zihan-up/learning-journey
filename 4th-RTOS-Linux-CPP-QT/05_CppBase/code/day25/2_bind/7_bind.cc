#include <iostream>
#include <functional>
#include <string>

using std::cout;
using std::endl;
using std::bind;
using std::function;
using std::string;

int add(int x, int y)
{
    cout << "int add(int, int)" << endl;
    return x + y;
}


void test()
{
    function<int()> f = bind(&add, 1, 2);
    cout << "f() = " << f() << endl;

    cout << endl;
    using namespace std::placeholders;
    function<int(int, int, int)> f2 = bind(add, _1, _3);
    function<int(int, string, int)> f3 = bind(add, _1, _3);
    function<int(int, string, string, int)> f4 = bind(add, _1, _4);
    f4(1, "wangdao", "hello", 10);
    function<int(int, int, int)> f5 = bind(add, _3, _1);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

