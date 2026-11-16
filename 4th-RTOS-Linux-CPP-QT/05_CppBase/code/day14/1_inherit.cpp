#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
    Base()
    :_data(10)
    {

    }

    //对于基类成员函数的隐藏
    void print(){
        cout << "Base::print()" << endl;
    }

//protected:
public:
    int _data;
};
//如果派生类中定义了和基类同名的变量，那么只能够访问到派生类自己的数据成员
//如果派生类中定义了和基类中同名的变量，那么便形成了隐藏（数据成员的隐藏）
//此时内存布局中是否是将基类的数据成员覆盖了呢？？？
//并没有覆盖，通过查看类对象的大小可以发现，数据成员依然是存在的
//如果实在想访问基类的？可以怎么办呢？？？类名::变量
class Derived : public Base{
public:
    Derived()
    :_data(20)
    {

    }
    void func(){
        cout << _data << endl;
    }
    //派生类中定义同名的print函数
    int print(int number){
        cout << "Derived::print" << number << endl;
    }
private:
    int _data;
};


void test(){
    cout << sizeof(Base) << endl;// 4
    cout << sizeof(Derived) << endl;//8
    Derived d;
    d.func();
    //这种方式可以访问到基类的数据成员，但是不是特别推荐
    cout << d.Base::_data << endl;
}

void test2(){
    Derived d;
    //如果派生类中没有定义同名的函数，继承父类的函数
    d.print();
    //但是一旦派生类中定义了同名的函数，那么便无法调用
    d.print(10);
    d.Base::print();//这种方式同样不是特别推荐
}

int main()
{
    test();
    return 0;
}

