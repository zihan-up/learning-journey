#include <string.h>
#include <iostream>
using std::cout;
using std::ostream;
using std::endl;
//继承体系下的复制控制函数
//第二阶段：
//不仅基类中有自己的指针数据成员，派生类中也有指针数据成员
//不仅基类需要编写析构函数、拷贝构造函数，赋值运算符
//派生类也同样需要编写
class Base{
public:
    Base(const char * pbase)
    :_pbase(new char[strlen(pbase) + 1]())
    {
        strcpy(_pbase, pbase);
        cout << "Base(const char *)" << endl;
    }
    Base(){}
    //拷贝构造函数
    Base(const Base & rhs)
    :_pbase(new char[strlen(rhs._pbase) + 1]())
    {
        cout << "Base(const Base &)" << endl;
        strcpy(_pbase, rhs._pbase);
    }
    //析构函数
    ~Base(){
        cout << "~Base()" << endl;
        if(_pbase){
            delete [] _pbase;
            _pbase = nullptr;
        }
    }
    //赋值运算符函数
    Base & operator=(const Base & rhs){
        cout << "Base::operator=()" << endl;
        if(this != &rhs){
            delete [] _pbase;
            _pbase = new char[strlen(rhs._pbase) + 1]();
            strcpy(_pbase, rhs._pbase);
        }
        return *this;
    }
//private:
protected:
    char * _pbase;
};
//但是此时因为派生类中的指针数据成员申请了堆空间
//主动写出析构函数、拷贝构造函数、赋值运算符函数---三合成原则
class Derived : public Base{
public:
    Derived(const char * base, const char * pderived)
    :Base(base)
    ,_pderived(new char[strlen(pderived) + 1]())
    {
        strcpy(_pderived, pderived);
    }
    friend ostream & operator<<(ostream & os, const Derived & rhs);

    ~Derived(){
        if(_pderived){
            delete [] _pderived;
            _pderived = nullptr;
        }
    }
    //会报错，为什么报错，如何解决呢？？？
    //使用一个派生类对象去创建一个新的派生类对象
    //对象的空间申请就绪，但是后续如何进行数据的填充呢？数据成员的初始化呢？？
    //需要借助于构造函数来完成数据成员的初始化
    //1.优先选择基类的无参构造函数来完成基类部分的初始化工作
    //2.如果没有,主动调用基类的拷贝构造函数来完成初始化
    Derived(const Derived & rhs)
    :Base(rhs)//调用基类的拷贝构造函数Base & ref = rhs;
    ,_pderived(new char[strlen(rhs._pderived) + 1]())
    {   
        strcpy(_pderived, rhs._pderived);
    }

    //代码有问题，此时仅调用了派生类的赋值运算符函数
    //但是并没有调用基类的
    //先调用基类的
    Derived & operator=(const Derived & rhs){
        if(this != &rhs){
            Base::operator=(rhs);
            delete [] _pderived;
            _pderived = new char[strlen(rhs._pderived) + 1]();
            strcpy(_pderived, rhs._pderived);

        }
        return *this;
    }

private:
    char * _pderived;
};


ostream & operator<<(ostream & os, const Derived & rhs){
    if(rhs._pbase){
        os << rhs._pbase;
    }
    if(rhs._pderived){
        os << rhs._pderived;
    }
   return os; 
}
void test(){
    //此时Derived中啥也没有，那么编译器会提供一个
    //默认的无参构造函数;会调用基类的无参构造函数完成初始化
    //基类的无参构造函数没有
    //Derived d1;
    //Derived d2 = d1;

    Derived d1("d1-base", "d1-derived");
    Derived d2 = d1;
    cout << d1 << ":" << d2 << endl;


    cout << "================" << endl;
    Derived d3("d3-base", "d3-derived");
    d3 = d1;
    cout << d1 << ":" << d3 << endl;
}

int main()
{
    test();
    return 0;
}

