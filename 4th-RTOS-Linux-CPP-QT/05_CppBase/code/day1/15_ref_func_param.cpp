#include <iostream>
using std::cout;
using std::endl;
//作为函数的参数
//编写3个swap函数
//并不能够起到swap交换的功能，为什么呢？？？？
//此时传递的是这个数值
//形参a和b需要进行初始化，初始化的值分别是x和y的值
//可以做一个事情，打印a b的地址以及x和y地址
void swap(int a, int b){
    cout << "swap函数内a的地址" << &a << ",b的地址" << &b << endl;
    int temp = a;
    a = b;
    b = temp;
}
//为什么swap2能够改变原先的操作数？？？
void swap2(int * pa, int * pb){
    cout << "swap2函数内pa的值" << pa << ",pb" << pb << endl;
    cout << "swap2函数内pa的地址" << &pa << ",pb的地址" << &pb << endl;
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}
//swap3里面的形参的地址值和实参的x和y地址值是完全一模一样的
//对于形参的任何操作，都会影响到实参
void swap3(int & a, int & b){
    cout << "swap3函数内a的地址" << &a << ",b的地址" << &b << endl;
    int temp = a;
    a = b;
    b = temp;
}

void test(){
    int x = 10, y = 20;
    cout << "x的地址:" << &x << ",y的地址:" << &y << endl;
    swap(x, y);
    cout << "经过swap交换之后x=" << x << ",_y=" << y << endl;
}
void test2(){
    int x = 10, y = 20;
    cout << "x的地址:" << &x << ",y的地址:" << &y << endl;
    swap2(&x, &y);
    cout << "经过swap2交换之后x=" << x << ",_y=" << y << endl;
}
void test3(){
    int x = 10, y = 20;
    cout << "x的地址:" << &x << ",y的地址:" << &y << endl;
    swap3(x, y);
    cout << "经过swap3交换之后x=" << x << ",_y=" << y << endl;

}

int main()
{
    test3();
    return 0;
}

