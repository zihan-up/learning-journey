#include <iostream>
#include <string>
using std::cout;
using std::endl;
//虚函数原理
class Base{
public:
    virtual
    void print(){
        cout << "Base::print()" << endl;
    }

    virtual
    void display(){
        cout << "Base::display()" << endl;
    }

private:
    long _base = 10;
};
class Derived : public Base{
public:
    void print(){

    }
private:
    long _derived = 20;
};
void test(){
    //基类和派生类的大小
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
    //就以基类为例
    Base base;
    Base * pbase = &base;
    long * pl = (long *)pbase;
    cout << *pl << endl;
    cout << *(pl + 1) << endl;

    cout << "===================" << endl;
    Derived d;
    Base * pbase2 =  &d;
    pbase2->print();
    pbase2->display();
}

int main()
{
    test();
    return 0;
}

