#include <iostream>
using std::cout;
using std::endl;
class Base{
private:
    int _base;
};

class Derived : public Base{


private:
    int _derived;
};


//可否把一个基类对象赋值给一个派生类对象？error
//可否把一个派生类对象赋值给一个基类对象？ok 
//可否将一个基类指针指向一个派生类对象？ok 
//可否将一个派生类指针指向一个基类对象？error
//可否将一个基类引用绑定一个派生类对象？ok 
//可否将一个派生类引用绑定一个基类对象？error
void test(){
    Base base;
    Derived derived;
    //derived = base;
    base = derived;

    Base * pbase = &derived;
    //Derived * pderived = &base;
    //
    Base & bref = derived;
    //Derived & dref =  base;
}

int main()
{
    test();
    return 0;
}

