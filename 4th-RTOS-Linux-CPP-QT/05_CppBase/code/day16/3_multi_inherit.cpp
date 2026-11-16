#include <iostream>
using std::cout;
using std::endl;

class A{
public:
    virtual void a(){ cout << "A::a()" << endl; }
    virtual void b(){ cout << "A::b()" << endl; }
    virtual void c(){ cout << "A::c()" << endl; }
};

class B{
public:
    virtual void a(){ cout << "B::a()" << endl; }
    virtual void b(){ cout << "B::b()" << endl; }
    void c(){ cout << "B::c()" << endl; }
    void d(){ cout << "B::d()" << endl; }
};

class C
: public A
, public B
{
public:
    virtual void a(){ cout << "C::a()" << endl; }
    void c(){ cout << "C::c()" << endl; }
    void d(){ cout << "C::d()" << endl; }
};


//先不看D类
class D
: public C
{
public:
    void c(){ cout << "D::c()" << endl; }
};


void test(){
      C c;
    c.a();//C::a() 没有通过虚表，隐藏，相当于把a()看成普通成员函数
    //成员名访问冲突二义性
    //c.b();//error,成员名访问冲突二义性
    c.c();//C::c(),本质是虚函数，没有通过虚表，隐藏 
    c.d();//C::d(),不是虚函数，隐藏
    
    cout << endl;
    A* pa = &c;
    pa->a();//C::a(),动态多态被触发 
    pa->b();//A::b(),调用A类定义的虚函数b(),通过虚表，没有覆盖,最终动态多态依然没有被激活 
    pa->c();//C::c(),动态多态被触发
    //pa->d();//error,只能调用A基类子对象的内容，无法调用
    
    cout << endl;
    B* pb = &c;
    pb->a();//C::a(), 动态多态触发 
    pb->b();//B::b(),通过虚表，但是没有覆盖,最终动态多态依然没有被激活
    //因为c不是虚函数，所以在编译时期就可以确认调用情况
    //直接确认调用基类里面的函数
    pb->c();//B::c(),调用B定义的普通成员函数c()
    pb->d();//B::d(),同上 


    cout << endl;
    C * pc = &c;
    pc->a();//C::a() 通过虚表，但是没有触发动态多态 
    //pc->b();//error 成员名访问冲突二义性 
    
    //思路：使用指针进行函数调用时，首先确认是否是虚函数
    //如果不是虚函数，那么就是普通的函数调用可以再编译
    //时期就直接确定
    //如果是虚函数，则会this->vfptr->vtable查找虚函数调用
    pc->c();//C::c(),本质是虚函数，通过虚表，不算动态多态 
    pc->d();//C::d(),不是虚函数，隐藏 

    //验证c究竟是不是虚函数
    D d;
    C * pc2 =  &d;
    pc2->c();
}

int main()
{
    test();
    return 0;
}

