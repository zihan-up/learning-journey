#include <iostream>
using std::cout;
using std::endl;


class A{
public:
    A(){
        cout << "A()" << endl;
    }

    ~A(){
        cout << "~A()" << endl;
    }

    void print(){
        cout << "A::print()" << endl;
    }

    long _a = 1;
};

class B{
public:
    B(){
        cout << "B()" << endl;
    }

    ~B(){
        cout << "~B()" << endl;
    }

    void print(){
        cout << "B::print()" << endl;
    }

    long _b = 2;
};

class C{
public:
    C(){
        cout << "C()" << endl;
    }

    ~C(){
        cout << "~C()" << endl;
    }

    void print(){
        cout << "C::print()" << endl;
    }

    long _c = 3;
};
class D
:public A
,public C
,public B
{
public:
    D(){
        cout << "D()" << endl;
    }

    ~D(){
        cout << "~D()" << endl;
    }

    //在派生类中定义一个同名的函数即可
     void print(){
         cout << "D::print()" << endl;
     }

    long _d = 4;
};


void test(){
    D d;
    //d.print();
    d.A::print();//不是特别推荐
    //子类进行隐藏
    d.print();
}

int main()
{
    test();
    return 0;
}

