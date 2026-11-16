#include <iostream>
using std::cout;
using std::endl;
//函数指针的使用
//实现一个简易的计算器的功能，实现加减乘除的运算
//在C++中，如果使用char *的话，强烈建议大家加上const修饰
//const char * pstr = "hello,world";
int add(int a, int b){
    return a + b;
}
int sub(int a, int b){
    return a - b;
}
int multiply(int a, int b){
    return a * b;
}
int divide(int a, int b){
    return a / b;
}
//const char * 利用==符号判断是否和后面的常量值相等
//strcmp
int calc(int leftNumber, const char * operation, int rightNumber){
    //定义一个函数指针，根据不同的情形，让这个指针
    //去指向不同的函数
    int (*pFunc)(int,int);
    if(operation == "+"){
        pFunc = &add;
    }else if(operation == "-"){
        pFunc = &sub;
    }else if(operation == "*"){
        pFunc = &multiply;
    }else if(operation == "/"){
        pFunc = &divide;
    }
    return pFunc(leftNumber, rightNumber);
}


void test(){
    cout << calc(10, "+", 20) << endl;
    cout << calc(10, "-", 20) << endl;
    cout << calc(10, "*", 20) << endl;
    cout << calc(20, "/", 10) << endl;
}

int main()
{
    test();
    return 0;
}

