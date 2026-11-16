#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
    Base(int number)
    :_number(number)
    {
        cout << "Base()" << _number  << endl;
    }
    ~Base(){
        cout << "~Base()" << _number << endl;
    }

private:
    int _number;
};
class Obj{
public:
    Obj(int number){
        cout << "Obj()" << endl;
    }
    ~Obj(){
        cout << "~Obj()" << endl;
    }

};


class Derived: public Base{
public:
    //首先会调用派生类额构造函数
    //随后会立刻调用基类的构造函数完成基类子对象部分的成员初始化
    //接下俩再根据声明的顺序，依次去调用对象成员的构造函数
    //最后再去执行派生类构造函数的函数体部分
    //注意：Base构造函数调用形式
    //以及给_base基类数据成员初始化形式
    Derived(int baseNumber, int objNumber)
    :Base(baseNumber)//调用基类的构造函数，完成基类子对象部分的初始化工作
    ,_obj(objNumber)
    ,_base(baseNumber * 2)//给基类的数据成员进行初始化工作
    {
        cout << "Derived()" << endl;
    }
    ~Derived(){
        cout << "~Derived()" << endl;
    }

private:
    Obj _obj;
    //如果此时派生类中持有基类对象数据成员呢？？
    Base _base;
    long _derived = 20;
};


void test(){
    Derived d(1 ,2 );
}

int main()
{
    test();
    return 0;
}

