#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
    Base(){
        cout << "Base()" << endl;
    }
    virtual
    ~Base(){
        cout << "~Base()" << endl;
    }
    virtual void print(){
        cout << "Base::print()" << endl;
    }
};
class Derived : public Base{
public:
    Derived(const char * name)
    :_name(new char[strlen(name) + 1]())
    {
        cout << "Derived(const char *)" << endl;
        strcpy(_name, name);
    }
    ~Derived(){
        cout << "~Derived" << endl;
        if(_name){
            delete [] _name;
            _name = nullptr;
        }
    }
    void print() override{
        cout << "Derived::print" << endl;
    }
private:
    char * _name;
};

void test(){
//场景：使用基类指针去指向位于堆区的派生类对象
//使用指针进行回收堆空间对象时
    Base * pbase = new Derived("hello");
    pbase->print();//符合多态激活的条件
    //delete pbase,先调用析构函数
    //但是由于析构函数设置为了虚函数，所以会走虚表
    //vfptr->vtable,查找到析构函数所在的地址
    //调用析构函数，调用的是派生类的析构函数
    //调用了派生类的析构函数之后，如何调用的基类的析构函数的呢？？？
    //实际上这是继承中基本语法规则
    //创建一个派生类对象会立马调用派生类的构造函数，随后调用基类的构造函数
    //销毁一个派生类对象会立马调用派生类的析构函数，随后调用基类的析构函数
    delete pbase;
}

int main()
{
    test();
    return 0;
}

