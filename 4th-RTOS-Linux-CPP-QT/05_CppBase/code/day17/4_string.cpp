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
    String s;
    String s2("hello");
    String s3 = s2;
    s = s2;
}
void test2(){
    //尝试画出此时对应的内存图示
    //通过内存图示，分析是否有资源上的浪费
    //拷贝构造函数
    String s = String("hello");
    String s2("world");
    //赋值运算符函数
    s2 = String("hell,python");
}

int main()
{
    test2();
    return 0;
}

