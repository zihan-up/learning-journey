#include <iostream>
using std::cout;
using std::endl;
class Base{
protected:
    Base(){
        cout << "Base()" << endl;
    }
};
class Derived : public Base{
public:
    Derived(){
        cout << "Derived()" << endl;
    }

private:
    //Base _ba;
};
void test(){
    //Base base;
    Derived d;
}

int main()
{
    test();
    return 0;
}

