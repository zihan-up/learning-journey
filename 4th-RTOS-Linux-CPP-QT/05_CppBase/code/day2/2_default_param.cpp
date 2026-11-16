#include <iostream>
using std::cout;
using std::endl;
//默认参数的设置一般情况会在函数的声明(函数的声明和定义分开的情况)中去设置
//声明
int add(int a = 0, int b = 0);

void test2(){
    cout << add(1, 4) << endl;
    //(如果默认参数设置在定义中)函数调用时，
    //只看到了函数的声明，没有看到定义，也就无从得知
    //默认参数的设置
    cout << add() << endl;
}


//定义
int add(int a, int b){
    return a + b;
}

void test(){

}

int main()
{
    test2();
    return 0;
}

