#include <iostream>
using std::cout;
using std::endl;
//各种虚函数调用场景分析
//1.通过对象直接调用？？？？就是普通的函数调用
//不满足动态多态激活的条件，也不会走虚函数表
//多态被激活肯定需要走虚函数表
//但是走虚函数表不一定动态多态一定被激活（派生类没有对基类覆盖）
class Base{
public:
    virtual
    void print(){
        cout << "Base::print()" << endl;
    }
};
class Derived: public Base{
public:
    void print() override{
        cout << "Derived::print()" << endl;
    }
};
void test(){
    Derived d;
    d.print();
}

int main()
{
    test();
    return 0;
}

