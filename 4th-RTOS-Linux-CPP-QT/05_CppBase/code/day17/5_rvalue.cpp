#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//深拷贝，没有运算符重载
class String{
public:
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }
    String()
    :_pstr(new char[1]())
    {}

    //析构函数
    ~String(){
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr;
        }
    }

    //拷贝构造函数
    String(const String & rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        cout << "String(const String & rhs)" << endl;
        strcpy(_pstr, rhs._pstr);
    }
    //赋值运算符函数
    String & operator=(const String & rhs){
        cout << "String & operator=" << endl;
        if(this != & rhs){
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }

    int size() const{
        return strlen(_pstr);
    }
    const char * c_str() const{
        return _pstr;
    }

private:
    char * _pstr;
};


void test(){
    int number = 10;
    cout << &number << endl;
    cout << &10 << endl;//error
    cout << &(10 + 20) << endl;
    cout << &String("hello") << endl;


    //引用：之前介绍分为两种，
    //一种是const引用:既可以绑定左值，也可以绑定右值
    //一种是非const引用：只可以绑定左值，所以称之为左值引用
    int & ref = number;
    //int & ref2 = 20;error

    const int & ref3 = number;
    const int & ref4 = 20;

    //现在我们的需求是什么？？？？？？？识别出右值
    //需要在代码层面能够识别出那一撮右值
    //希望有一个和左值引用相对应的东西，右值引用：
    //只可以绑定右值，没法绑定左值
    int && rref1 = 10;
    //int && rref2 = number;没法去绑定左值
    String && rref3 = String("hello");
    String s2("hello");
    String && rref4 = s2;
}

int main()
{
    test();
    return 0;
}

