#include <string.h>
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

//深拷贝，没有运算符重载
class String{
public:
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
    }
    String()
    :_pstr(new char[1]())
    {}

    //析构函数
    ~String(){
        cout << "~String()" << endl;
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
    //移动构造函数:不再执行深拷贝，而是将控制权进行移交
    //String s = String("hello");
    String(String && rhs)
    :_pstr(rhs._pstr)
    {
        cout << "String(String &&)" << endl;
        rhs._pstr = nullptr;
    }
    //移动赋值运算函数：将控制权进行移交
    String & operator=(String && rhs){
        cout << "String::operator=(String &&)" << endl;
        //Q:自赋值判断还需要吗？？？？？？
        if(this != &rhs){
            delete [] _pstr;
            _pstr = rhs._pstr;
            //过河拆桥
            rhs._pstr = nullptr;
        }
        return *this;
    }

    int size() const{
        return strlen(_pstr);
    }
    const char * c_str() const{
        return _pstr;
    }

    friend ostream & operator<<(ostream & os, const String & rhs);
private:
    char * _pstr;
};
ostream & operator<<(ostream & os, const String & rhs){
    if(rhs._pstr){
        os << rhs._pstr;
    }
    return os;
}

//调用一次构造函数
String globalStr("hello,world");

String func1(){
    //调用一次拷贝构造函数
    return globalStr;
}

String func2(){
    //调用了一次构造函数
    String localStr("hello,world");
    //调用的是移动构造函数
    return localStr;
}

void test(){
    //func1();
    func2();
}

int main()
{
    test();
    return 0;
}

