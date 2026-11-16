#include <iostream>
using std::cout;
using std::endl;
//C++的内存布局
//栈区：栈变量、栈对象、局部变量、局部对象
//堆区：malloc/new操作的空间

//全局静态区：全局变量、静态变量
//文字常量区：文字常量、全局的常量
//程序代码区：代码
int globalNum = 30;
static int staticNumber = 40;
const int constNumber = 50;
void test(){
    //number属于局部变量、栈变量
    int number = 10;
    int number2 = 10;
    //pInt属于堆区嘛？属于栈区
    //本身是一个栈变量，只不过里面存储的地址是堆的地址
    int * pInt = new int(20);
    cout << &number << endl;
    cout << &number2 << endl;
    cout << &pInt << endl;
    //打印的便是堆区的地址，为什么呢？
    //对于指针变量来说，存储的就是地址值
    cout << pInt << endl;
    cout << "===================" << endl;
    //也是位于全局静态区的
    static int staticNumber2 = 50;
    cout << &globalNum << endl;
    cout << &staticNumber << endl;
    cout << &staticNumber2 << endl;//静态区
    cout << "============文字常量区=======" << endl;
    const char * pstr = "hello,world";
    //hello,world位于文字常量区的
    cout << (void *)pstr << endl;
    cout << &"hello,world" << endl;
    cout << &constNumber << endl;
    //局部变量的常量位于栈区
    const int constNumber2 = 80;
    cout << &constNumber2 << endl;
    //当前的test函数就是位于程序代码区的
    //函数指针，cout对于函数指针的输出没有定义的
    //只会固定的输出1或者0，如果有则是1如果没有则是0
    //依然是强转为void *即可
    cout << "========程序代码区=======" << endl;
    cout << (void *)test << endl;
}

int main()
{
    test();
    return 0;
}

