#include <iostream>
using std::cout;
using std::endl;
//引用：可以理解为是一个变量的别名
void test(){
    int number = 10;
    //注意：此时&符号表示的含义是引用，并不是取地址
    //问题：如何区分什么时候表示的是取地址、什么时候表示的是引用
    //如果&前面有数据类型(强转除外)那么就表示的是引用
    int & ref = number; //引用
    cout << &number << endl;//取地址
    //int & ref2;error 引用必须得绑定到某个特定的变量
}
//下面的代码演示了什么规律？？？？？
//引用一旦绑定，无法再次绑定（从一而终）
//对于引用的操作修改会直接影响到变量的本体
void test2(){
    int number = 10;
    int & ref = number;
    int number2 = 20;
    ref = number2;//这步代表什么意思？？？赋值操作
    cout << number << endl;
    cout << ref << endl;
    cout << number2 << endl;
    cout << &number << endl;
    cout << &ref << endl;
    cout << &number2 << endl;
    number2 = 30;
    cout << "=================" << endl;
    cout << number << endl;
    cout << ref << endl;
    cout << number2 << endl;
    cout << &number << endl;
    cout << &ref << endl;
    cout << &number2 << endl;
}

int main()
{
    test2();
    return 0;
}

