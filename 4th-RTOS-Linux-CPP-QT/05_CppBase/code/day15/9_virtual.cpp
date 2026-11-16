#include <iostream>
using std::cout;
using std::endl;
//在普通成员函数中调用虚函数
//深入：只要我们使用指针来调用函数，只要存在虚函数指针，都会走虚函数表
//但是究竟能不能起到多态的效果，那么就取决于代码的编写
class Base{
public:
    Base(){
        cout << "Base()" << endl;
    }

    virtual
        void print(){
            cout << "Base::print" << endl;
        }

    //隐含的this指针   Base * const this
    //derived.func1()-------> func1(&derived);
    // Base * const this = &Derived;
    // this->print();
    //this指针的形式：形参和实参的结合
    //Base * const this = &derived;
    //this->print();
    //Base * pbase2 = &derived;
    //pbase2->func1();------->func1(pbase2);
    //Base * const this = pbase2;进一步转换
    //Base * const this = &derived;
    //this->print();
    void fun1(){
        this->print();
    }

    //凡是使用了func2全部都不满足多态
    //因为根本不可能展示出多态的效果
    void fun2(){
        Base::print();
    }

};

class Derived
:public Base
{
public:
    Derived(){
        cout << "Derived()" << endl;
    }
    //虚函数，派生类进行了覆盖重写
    void print(){
        cout << "Derived::print" << endl;
    }
};

void test(){
    Base base;
    Derived derived;
    //1和2不满足多态
    //Base * pbase = &derived;
    //pbase->print();
    base.fun1();//(1)
    base.fun2();//(2)

    derived.fun1();//(3)满足多态
    derived.fun2();//(4)

    cout << "============" << endl;

    //56肯定也不会满足多态
    Base * pbase = &base;
    pbase->fun1();//(5)
    pbase->fun2();//(6)
    cout << "------------------" << endl;
    Base * pbase2 = &derived;
    pbase2->fun1();//(7)
    pbase2->fun2();//(8)
}

int main()
{
    test();
    return 0;
}

