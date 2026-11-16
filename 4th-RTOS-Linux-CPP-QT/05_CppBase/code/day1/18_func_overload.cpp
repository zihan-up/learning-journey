#include <iostream>
using std::cout;
using std::endl;
//函数重载：可以定义出一系列具有相同名称的函数
//肯定还有其他的要求？？？？
//注意：函数重载中函数的返回值不是区分的标志 add(1, 2);
//函数的参数列表是函数重载能够区分的标志
//函数参数的个数、参数类型、参数顺序的组合
//上述的三个指标只要能够形成区分度，能够区分出彼此，那么
//便可以形参函数重载
int add(int a, int b){
    return a + b;
}
int add(int a, int b, int c){
    return a + b + c;
}
double add(double a, double b){
    return a + b;
}

double add(int a, double b){
    return a + b;
}
double add(double a, int b){
    return a + b;
}


void test(){

}

int main()
{
    test();
    return 0;
}

