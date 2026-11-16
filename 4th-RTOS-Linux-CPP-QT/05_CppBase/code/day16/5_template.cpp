#include <iostream>
using std::cout;
using std::endl;
//模板的引入
//编写一系列的add函数
#if 0
int add(int a, int b){
    return a + b;
}
double add(double a, double b){
    return a + b;
}
short add(short a, short b){
    return a + b;
}
//定义类 Stack
class Stack{

private:
    int * _data;
};
#endif


//编写一个函数模板，便可以解决上述问题
//模板中可以把类型当做参数
//只需要编写这一个函数即可，调用时，会根据变量的类型，进行对应的实例化
template <class T>
T add(T a, T b){
    cout << "template" << endl;
    return a + b;
}

//test函数里面进行了三次调用，最终依然需要有三个不同类型的add函数重载存在
//只不过这个时候无需开发人员去做这个事情
//而是由编译器自动生成
//vector<int> number;
void test(){
    int a = 10, b = 20;
    cout << add(a, b) << endl;
    double c = 10.6, d = 30.9;
    cout << add(c, d) << endl;
    short e = 10,  f =20;
    cout << add(e, f) << endl;

    //上面的代码全部都是隐式实例化
    //
    //显式实例化
    cout << add<int>(a, b) << endl;

    cout << add<int>(c, d) << endl;
}
void test2(){
    int a = 10;
    double b = 20.6;
    //此时因为无法处理不同类型变量的相加，导致了出错
    //可以有两种解决方案：
    //1.显式实例化，强制指定一个类型
    //2.实现函数模板的重载
    cout << add(a, b) << endl;
}

int main()
{
    test2();
    return 0;
}

