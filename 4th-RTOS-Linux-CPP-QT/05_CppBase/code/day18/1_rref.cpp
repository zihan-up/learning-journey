#include <iostream>
using std::cout;
using std::endl;

int number = 10;
int && func(){
    //可以把一个左值转换成右值
    //但是说是这么说，但是底层并没有做任何高深的处理
    //仅仅只是做了一个类型转换
    return std::move(number);
}
//这种形式可以写吗？？？？
//依然不可以这么写，为什么？因为函数执行完毕之后
//该变量会被销毁，无论是左值引用还是右值引用都不可以
//去绑定一个已经销毁的变量
int && func2(){
    int a = 10, b = 20;
    //return (1 + 2);
    return (a + b);
}
void test2(){
    //后续对于ref的操作全部都是未定义行为
    int && ref = func2();
}

void test(){
    cout << &number << endl;
    int && ref = func();
    //返回的右值引用究竟是左值还是右值
    //依然是取决于这个引用变量本身是否有名称
    //有名称便是左值，可以取地址
    //没有名称便是右值，不可以取地址
    cout << &ref << endl;
    //cout << &func() << endl;
}

int main()
{
    test();
    return 0;
}

