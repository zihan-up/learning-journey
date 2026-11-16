#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
    Base(){
        cout << "Base()" << endl;
    }
    ~Base(){
        cout << "~Base()" << endl;
    }

private:
    long _base=10;
};
class Derived: public Base{
public:
    Derived(){
        cout << "Derived()" << endl;
    }
    ~Derived(){
        cout << "~Derived()" << endl;
    }

private:
    long _derived = 20;
};


void test(){
    //大小是16字节
    //其中Base是8字节
    //Derived只持有一个long类型的数据成员
    //吸收基类的数据成员
    //此时内存布局如何呢？？？？
    //使用Derived*类型指针指向一个派生类对象
    //将上述指针强转为long*指针
    //对指针进行移动，进行解引用操作
    Derived d;
    cout << sizeof(d) << endl;//16
    Derived * p = &d;
    long * pl = (long *)p;
    cout << *pl << endl;//10
    cout << *(pl + 1) << endl;//20
    //Base b;
    //cout << sizeof(b) << endl;
}

int main()
{
    test();
    return 0;
}

