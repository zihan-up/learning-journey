#include <iostream>
using std::cout;
using std::endl;


class Grandpa
{
public:
    Grandpa(){ cout << "Grandpa()" << endl; }
    ~Grandpa(){ cout << "~Grandpa()" << endl; }

    virtual void func1() {
        cout << "Grandpa::func1()" << endl;
    }

    virtual void func2(){
        cout << "Grandpa::func2()" << endl;
    }
};

class Parent
: public Grandpa
{
public:
    //构造函数和析构函数中调用虚函数，调用的是谁的虚函数？？？在本案例中，调用的全部都是grandpa的
    //满足多态激活的条件嘛？？？？不满足
    //Parent的构造函数中只能够看到Grandpa的信息
    Parent(){
        cout << "Parent()" << endl;
        //func1();//构造函数中调用虚函数
    }

    ~Parent(){
        cout << "~Parent()" << endl;
        //func2();//析构函数中调用虚函数
    }
};

class Son
: public Parent
{
public:
    Son() { cout << "Son()" << endl; }
    ~Son() { cout << "~Son()" << endl; }

    virtual void func1() override {
        cout << "Son::func1()" << endl;
    }

    virtual void func2() override{
        cout << "Son::func2()" << endl;
    }
};

void test(){
    //标准的多态
    Son ss;
    Grandpa * p = &ss;
    p->func1();
    p->func2();
}


int main()
{
    test();
    return 0;
}

