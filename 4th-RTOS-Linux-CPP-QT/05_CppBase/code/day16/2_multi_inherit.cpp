#include <iostream>
using std::cout;
using std::endl;
class Base1{
public:
    Base1()
    :_iBase1(10)
    {
        cout << "Base1()" << endl;
    }

    virtual void f(){
        cout << "Base1::f()" << endl;
    }

    virtual void g(){
        cout << "Base1::g()" << endl;
    }

    virtual void h(){
        cout << "Base1::h()" << endl;
    }

    virtual ~Base1(){
        cout << "~Base1()" << endl;
    }

private:
    double _iBase1;
};

class Base2{
    public:
        Base2()
        :_iBase2(20)
        {
            cout << "Base2()" << endl;
        }
    
        virtual void f(){
            cout << "Base2::f()" << endl;
        }
    
        virtual void g(){
            cout << "Base2::g()" << endl;
        }
    
        virtual void h(){
            cout << "Base2::h()" << endl;
        }
    
        virtual ~Base2(){
            cout << "~Base2()" << endl;
        }
    
    private:
        double _iBase2;
};

class Base3{
    public:
        Base3()
        :_iBase3(30)
        {
            cout << "Base3()" << endl;
        }
    
        virtual void f(){
            cout << "Base3::f()" << endl;
        }
    
        virtual void g(){
            cout << "Base3::g()" << endl;
        }
    
        virtual void h(){
            cout << "Base3::h()" << endl;
        }
    
        virtual ~Base3(){
            cout << "~Base3()" << endl;
        }
    
    private:
        double _iBase3;
};

class Derived 
	: public Base1
	, public Base2
	, public Base3
{
public:
	Derived()
	: _iDerived(10000) 
	{ cout << "Derived()" << endl; }

	void f() override
	{
		cout << "Derived::f()" << endl;
	}

	void g1()
	{
		cout << "Derived::g1()" << endl;
	}
private:
	double _iDerived;
};



void test(){
    Derived d;
    cout << &d << endl;
    cout << sizeof(d) << endl;
    //问题：p1 P2 P3打印的地址值一样吗？？？？
    //打印的地址值是不一样的
    Base1 * p1 = &d;
    Base2 * p2 = &d;
    Base3 * p3 = &d;
    cout << p1 << ":" << p2 << ":" << p3 << endl;
}

int main()
{
    test();
    return 0;
}

