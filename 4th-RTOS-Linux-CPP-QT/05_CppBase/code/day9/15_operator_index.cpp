#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//下标访问运算符
void test(){
    //string对于下标访问运算符进行了重载
    string s1 = "hello";
    cout << s1[0] << endl;
}

class String{
public:
    String()
    :_pstr(new char[1]())
    {

    }
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }

    char & operator[](size_t index){

    }

private:
    char * _pstr;
};

void test2(){
    String s2 = "hello";
    cout << s2[0] << endl;
}

int main()
{
    test();
    return 0;
}

