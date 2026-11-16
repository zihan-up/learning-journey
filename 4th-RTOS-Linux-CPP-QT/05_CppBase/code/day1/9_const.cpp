#include <iostream>
using std::cout;
using std::endl;
//const修饰内置数据类型
void test(){
    //const int number;error number没有被初始化
    const int number = 10;
}
//const修饰指针数据类型
void test2(){
    int number = 10;
    int number2 = 20;
    int * p = &number;
    cout << p << endl;
    cout << *p << endl;
    //对于指针的操作，其实就是两个层面：
    //一个是变更指向，
    //一个是变更指针指向的值
    p = &number2;//变更指向
    //通过指针去操作，也会影响到变量本体的值
    *p = 30;//变更指针所指向的值
    cout << number2 << endl;

    //const修饰的是*p2
    const int * p2 = &number;
    //*p2 = 30;error不可以
    p2 = &number2;
    //const修饰的是p3
    int *  const p3 = &number;
    //p3 = &number2;error 指针被const修饰，里面的地址值不可以变更的
    *p3 = 30;
}

void test3(){
    int number = 20;
    int number2 = 20;
    const int * const p = &number;
    //p = &number2;error 
    //*p = 30;error 
}

int main()
{
    test2();
    return 0;
}

