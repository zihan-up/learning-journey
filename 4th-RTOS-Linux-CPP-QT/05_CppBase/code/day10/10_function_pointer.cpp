#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::cerr;
//使用函数指针来完成一个简易计算器的功能
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
#if 0
//这是第一章介绍的版本
int calc(int leftNumber, const string & operation, int rightNumber){
    //声明一个函数指针
    int (*pFunc)(int,int);
    if(operation == "+"){
        pFunc = add;
    }else if(operation == "-"){
        pFunc = sub;
    }else if(operation == "*"){
        pFunc = multiply;
    }else if(operation == "/"){
        pFunc = divide;
    }else{
        cerr << "operation not support" << endl;
        return 0;
    }
    return pFunc(leftNumber, rightNumber);
}
#endif
//运算符重载中版本
int calc(int leftNumber, const string & operation, int rightNumber){
    //声明一个函数指针
    typedef int (*pFunc)(int,int);
    //把一个函数像对象一样去组织
    pFunc pf;
    if(operation == "+"){
        //pFunc = add;
        pf = add;
    }else if(operation == "-"){
        //pFunc = sub;
        pf = sub;
    }else if(operation == "*"){
        //pFunc = multiply;
        pf = multiply;
    }else if(operation == "/"){
        //pFunc = divide;
        pf = divide;
    }else{
        cerr << "operation not support" << endl;
        return 0;
    }
    //return pFunc(leftNumber, rightNumber);
    return pf(leftNumber, rightNumber);
}

void test(){
    cout << calc(20, "+", 10) << endl;
    cout << calc(20, "-", 10) << endl;
    cout << calc(20, "*", 10) << endl;
    cout << calc(20, "/", 10) << endl;
}

int main()
{
    test();
    return 0;
}

