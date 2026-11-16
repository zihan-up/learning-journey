#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//多态效果演示
class Base{
public:
    //virtual
    void print(){
        cout << "Base::print()" << endl;
    }

private:
    long _base;
};
class Derived : public Base{
public:
     Derived(const string & name)
         :_word(name){

         }

    void print(){
        cout <<  _word << "Derived::print()" << endl;
    }

private:
    long _derived;
    string _word;
};
void test(){
    //基类和派生类的大小
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
    //
    //使用指针去调用函数
    Base base;
    Derived derived("d1");
    Derived derived2("d2");

    Base * pbase = &base;
    pbase->print();
    Derived * pderived = &derived;
    pderived->print();
    cout << "==============" << endl;
    Base * pbase2 = &derived;
    pbase2->print();
    pbase2 = &derived2;
    pbase2->print();
}

int main()
{
    test();
    return 0;
}

