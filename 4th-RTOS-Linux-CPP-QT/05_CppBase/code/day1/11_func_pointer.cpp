#include <iostream>
using std::cout;
using std::endl;
//函数指针和指针函数
//函数指针：它是一个指针，该指针指向的是一个函数
//指针函数：它是一个函数，该函数的返回值是一个指针

int add(int a, int b){
    return a + b;
}

void test(){
    //可以对这个函数进行取地址操作
    //能否定义一个指针去指向该函数呢？
    //函数指针
    cout << (void *)&add << endl;
    //函数指针如何定义呢？？？
    //返回类型  指针变量名称(函数的参数列表) = 指向的函数的名称
    int (*p)(int,int) = add;
    cout << add(1, 2) << endl;
    cout << p(1, 2) << endl;
}

//指针函数
int globalNum = 30;
int * func(){
    return &globalNum;
}

int main()
{
    test();
    return 0;
}

