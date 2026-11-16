#include <string.h>
#include <iostream>
using std::cout;
using std::ostream;
using std::endl;
//继承体系下的复制控制函数
//第一阶段：
//派生类中不定义任何的数据成员，
//基类中定义一个指针数据成员，编写对应的拷贝构造函数、赋值运算符函数
class Base{
public:
    Base(const char * pbase)
    :_pbase(new char[strlen(pbase) + 1]())
    {
        strcpy(_pbase, pbase);
        cout << "Base(const char *)" << endl;
    }
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
//2.如果派生类中定义了自己的指针数据成员，在构造函数中进行了堆空间的申请
//但是此时依然没有主动去写拷贝构造函数和赋值运算符
//那么此时实际上会有内存泄漏的问题
class Derived : public Base{
public:
    Derived(const char * base, const char * pderived)
    :Base(base)
    ,_pderived(new char[strlen(pderived) + 1]())
    {
        strcpy(_pderived, pderived);
    }
    friend ostream & operator<<(ostream & os, const Derived & rhs);


private:
    char * _pderived;
};


ostream & operator<<(ostream & os, const Derived & rhs){
    if(rhs._pbase){
        os << rhs._pbase;
    }
   return os; 
}
void test(){
    //此时Derived中啥也没有，那么编译器会提供一个
    //默认的无参构造函数;会调用基类的无参构造函数完成初始化
    //基类的无参构造函数没有
    //Derived d1;
    //Derived d2 = d1;

    Derived d1("hello", "world");
    Derived d2 = d1;
    cout << d1 << ":" << d2 << endl;
}

int main()
{
    test();
    return 0;
}

