#include <iostream>
using std::cout;
using std::endl;


class A
{
public:
    void print() const{
        cout << "A::print()" << _a << endl;
    }
    double _a;
};

class B
: public A
{
public:
    double _b;
};

class C
: public A
{
public:
    double _c;
};

class D
: public B
, public C
{
public:
    void print(){

    }
    double _d;
};


void test(){
    D d;
    d.print();
}

int main()
{
    test();
    return 0;
}

