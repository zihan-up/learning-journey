#include <iostream>
using std::cout;
using std::endl;
//覆盖
class Base{
public:
    virtual
    void display(){
        cout << "Base::display" << endl;
    }
private:
    long _base;
};
class Derived: public Base{
public:
    void display() override{
        cout << "derived::display" << endl;
    }
 
private:
    long _derived;
};
void test(){
    Derived d;
    Base * pb = &d;
    pb->display();
}

int main()
{
    test();
    return 0;
}

