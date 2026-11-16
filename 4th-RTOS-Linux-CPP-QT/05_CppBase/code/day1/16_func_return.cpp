#include <iostream>
using std::cout;
using std::endl;
//引用作为函数的返回值

int func(){
    //这里面我们定义了一个局部变量a
    //当func函数执行完毕之后，a便会被销毁
    //期间有没有拷贝复制的过程？？？？有的
    int a = 10;
    //也就是说，在没有使用引用的情况下，return结果时
    //会有一次拷贝复制的过程
    cout << &a << endl;
    return a;
}

void test(){
    int b = func();
    //在c++中，称之为右值，右值可以理解为临时对象，临时变量
    //不可以进行取地址操作
    //cout << &func() << endl;
    cout << func() << endl;
    cout << b << endl;
    cout << &b << endl;
}

//无论在任何场景下，打印number或者ref的地址，始终是相同的
//引用作为函数的返回值，可以避免拷贝复制的过程
int number = 20;
int & func2(){
    cout << "func2::" << &number << endl;
    return number;
}
void test2(){
    cout << &number << endl;
    int & ref = func2();
    cout << &ref << endl;
}
//有一个情况需要注意：
//引用一定不要绑定到一个局部变量
int & func3(){
    int number = 30;
    cout << "func3::" << &number << endl;
    return number;
}

void test3(){
    int & ref = func3();
    cout << ref << endl;
    cout << &ref << endl;
}

void test4(){
    int number = 10;
    int & ref = number;
    int * p = &number;
    cout << sizeof(ref) << endl;
    cout << sizeof(p) << endl;
}

int main()
{
    test4();
    return 0;
}

