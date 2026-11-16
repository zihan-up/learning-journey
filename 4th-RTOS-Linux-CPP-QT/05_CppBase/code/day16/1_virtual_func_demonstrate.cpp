#include <iostream>
using std::cout;
using std::endl;
//虚表验证
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

virtual
  void show(){
      cout << "Base::show()" << endl;
  }

private:
long _base = 10;
};

class Derived
: public Base
{
public:
  void print(){
      cout << "Derived::print()" << endl;
  }

  void display(){
      cout << "Derived::display()" << endl;
  }

  void show(){
      cout << "Derived::show()" << endl;
  }

private:
long _derived = 100;
};
void test(){
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
    Derived d;
    Base * pbase = &d;
    //使用指针去调用print函数时，额外处理机制
    //this->vfptr->vtable[xx](virtual function address)----->call function

    pbase->print();
    cout << "==================" << endl;
    //24字节
    Derived * pderived = &d;
    //pl指针里面存储的地址和pderived里面存储的地址是一样的
    //但是pl + 1和pderived + 1得到的结果是完全不同的
    //8字节
    long * vfptr = (long *)pderived;
    cout << *(vfptr + 1) << endl;//访问的是_base的值
    cout << *(vfptr + 2) << endl;//访问的是_derived的值

    //对于虚函数指针再次进行解引用i
    //第一次解引用
    long * vtable = (long *)*vfptr;

    //运算符重载章节  函数指针的使用
    typedef void (*pFunc)(void);
    pFunc pf;
    //第二次解引用
    //print()函数
    pf = (pFunc)*vtable;
    pf();
    //display函数
    pf = (pFunc)*(vtable + 1);
    pf();
    //show函数
    pf = (pFunc)*(vtable + 2);
    pf();
}

int main()
{
    test();
    return 0;
}

