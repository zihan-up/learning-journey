#include <iostream>

using std::cout;
using std::endl;

//作用域与可见域
void test()
{
    int number = 123;
    //[]是捕获列表, 在lambda表达式的函数体中，不能直接访问外部局部变量，
    //除非在捕获列表中进行捕获
    //()函数的参数列表
    //{}函数的函数体
    //
    //两种捕获方式
    //1、值捕获：将外部局部变量以值传递的方式在lambda表达式中进行访问(也就是拷贝
    //到lambda表达式中)，此时是不能对该变量进行修改的，如果一定要进行修改，可以
    //使用mutable关键字进行修饰
    //2、引用捕获：将外部局部变量以引用的方法在lambda表达式中进行访问，但是此时
    //可以在lambda表达式中对引用捕获的变量进行修改(因为是引用，所以外部该变量
    //也会修改)
    /* [number](int value)mutable{ */
    [&number](int value){
        ++value;
        cout << "value = " << value <<endl;
        ++number;
        cout << "number = " << number << endl;
    }(10);

    cout << "外部访问number = " << number << endl;

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

