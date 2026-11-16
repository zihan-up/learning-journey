#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
    A(double a)
    : _a(a)
    {
        cout << "A(double)" << endl;
    }

    ~A(){cout << "~A()" << endl;}
private:
    double _a = 10;
};

class B
: virtual public A
{
public:
    B(double a, double b)
    : A(a)
    , _b(b)
    {
        cout << "B(double,double)" << endl;
    }

    ~B(){ cout << "~B()" << endl; }
private:
    double _b;
};


class C
: virtual public A
{
public:
    C(double a, double c)
    : A(a)
    , _c(c)
    {
        cout << "C(double,double)" << endl;
    }

    ~C(){ cout << "~C()" << endl; }
private:
    double _c;
};
//
class D
: public B,public C{
public:
    //注意此时构造函数的写法
    //不仅需要调用B和C构造函数
    //还需要调用A的构造函数
    D(double a, double b, double c, double d)
    :A(a)
    ,B(a, b)
    ,C(a, c)
    ,_d(d)
    {

    }

private:
    double _d;
 };


void test(){

}

int main()
{
    test();
    return 0;
}

