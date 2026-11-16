#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
    A(){ cout << "A()" << endl; }
    ~A(){ cout << "~A()" << endl; }
    void print() const{
        cout << "A::print()" << endl;
    }
};

class B
{
public:
    B(){ cout << "B()" << endl; }
    ~B(){ cout << "~B()" << endl; }
    void show() const{
        cout << "B::show()" << endl;
    }
};

class C
{
public:
    C(){cout << "C()" << endl; }
    ~C(){ cout << "~C()" << endl; }
    void display() const{
        cout << "C::display()" << endl;
    }
};

//内存布局的排布顺序和继承的先后顺序是相关的
//比如继承A,B,C那么在派生类的内存布局中A,B,C,D顺序
//还有一点主意事项: :public A,B,C并不是表示公有继承A B C
//而是表示公有继承A，私有继承B C
//如果希望公有继承A B C
//: public A, public B, public C
class D
: public A
,public B
, public C
{
public:
    D(){ cout << "D()" << endl; }
    ~D(){ cout << "~D()" << endl; }
    //void print() const{
    //    cout << "D::print()" << endl;
    //}
};



void test(){
    //要能够绘制出对应的内存模型
    //基类在前，派生类在后
    D d;
    d.print();
    d.show();
    d.display();
}

int main()
{
    test();
    return 0;
}

