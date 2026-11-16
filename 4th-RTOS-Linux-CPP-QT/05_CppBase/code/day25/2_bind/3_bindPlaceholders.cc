#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

void func(int x1, int x2, int x3, const int &x4, int x5)
{
    cout << "x1 = " << x1 << endl
         << "x2 = " << x2 << endl
         << "x3 = " << x3 << endl
         << "x4 = " << x4 << endl
         << "x5 = " << x5 << endl;
}

void test()
{
    //占位符整体代表的是函数的形参
    //占位符中的数字代表的是函数的实参
    //函数在传递实参的时候，实参的个数一定要大于等于占位符中的数字的最大值
    //bind的默认传递方式是值传递
    //如果想使用引用传递，可以使用引用的包装器
    //std::ref = reference
    //std::cref = const reference
    using namespace std::placeholders;
    int number = 100;
    auto f = bind(func, 10, _1, _2, std::cref(number), number);
    number = 200;
    f(11, 12, 44, 135, 666, 777, 888, 999);//没有使用的参数直接丢弃
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

