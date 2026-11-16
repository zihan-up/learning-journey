#include <iostream>
#include <string>
using std::cout;
using std::endl;
//虚函数原理
class Base{
public:
    //virtual
    void print(){
        cout << "Base::print()" << endl;
    }

private:
    long _base = 10;
};
class Derived : public Base{
public:
    void print(){
        cout << "derived::print" << endl;
    }
private:
    long _derived = 20;
};
class Derived2 : public Base{
public:
    void print(){
        cout << "Derived2::print()" << endl;
    }
private:
    long _derived = 20;
};
//多态：基类指针指向派生类对象，根据派生类对象的不同，代码执行过后
//产生的结果也是不同的
void test2(){
    Derived d;
    Derived2 d2;
    //多态的体现
    Base * pbase;
    pbase = &d;
    pbase->print();

    pbase = &d2;
    pbase->print();
}
//多态的底层原理：借助于虚函数
//虚函数？成员函数标注了virtual关键字，那么便是虚函数
//虚函数主要的使用场景便是用来去实现多态
void test(){
    Base base;
    Derived d;
    cout << sizeof(base) << endl;
    cout << sizeof(d) << endl;

    Base * pb = &base;
    Derived * pd = &d;

    long * pl1 = (long *)pb;
    cout << *pl1 << endl;
    cout << *(pl1 + 1) << endl;
    cout << "================" << endl;

    long * pl2 = (long *)pd;
    cout << *pl2 << endl;
    cout << *(pl2 + 1) << endl;
    cout << *(pl2 + 2) << endl;


}
int main()
{
    test2();
    return 0;
}

