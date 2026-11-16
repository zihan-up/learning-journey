#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class String{
public:
    String()
    :_pstr(new char[1]())
    {
        
    }
    //添加了 该关键字表示禁止隐式类型转换
    //explicit
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1])
    {
        strcpy(_pstr, pstr);
        cout << "String(const char * )" << endl;
    }
private:
    char * _pstr;
};

void test(){
    String s("hello");
    String s2 = "hello";
}

int main()
{
    test();
    return 0;
}

