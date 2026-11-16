#include <iostream>
using std::cout;
using std::endl;
//设计一个针对不同数据类型进行求和的函数比如int、double、float
//需要设置一个出口
//1.可以设置一个无参的
//2.可以设置一个一参的，函数模板
template <class T>
T sum(T t){
    return t;
}

template <class T, class ...Args>
T sum(T t, Args ...args){
    return t + sum(args...);
}

void test(){
    cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << endl;
    cout << sum(10.1, 10.5, 20.3, 45.6, 89.7) << endl;
}

int main()
{
    test();
    return 0;
}

