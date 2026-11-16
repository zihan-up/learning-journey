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

void test(){
    //需要添加去优化指令
    String s = String("hello");
}
void test2(){
    String s("hello");
    s = String("world");
}
void test3(){
    String s("hello");
    cout << s << endl;
    //使用std::move对s进行处理，去掉自赋值判断，查看究竟会如何??
    //s = s;这个操作有操作数是左值，不会走移动赋值运算函数
    s = std::move(s);// 这个会走移动赋值运算函数
    //std::move本质就是做了一个类型转换，加上了&&符号
    //欺骗了编译器，能够使用移动赋值运算函数
    cout << s << endl;
}

int main()
{
    test3();
    return 0;
}

