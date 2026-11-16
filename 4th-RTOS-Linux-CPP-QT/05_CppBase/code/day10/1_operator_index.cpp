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
    //无参构造函数
    String()
    :_pstr(new char[1]())
    {

    }
    //有参构造函数
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }

    //提供一个函数，展示出当前字符串的长度
    int size() const {
        return strlen(_pstr);
    }

    //需要对下标访问运算符进行重载i
    //这个地方必须得返回引用，否则无法修改操作数
    //也就是无法修改字符数组
    char & operator[](size_t index){
        if(index >= size()){
            //下标越界
            //位于静态区
            static char nullchar = '\0';
            //static Singleton s;
            return nullchar;
        }
        return _pstr[index];
    }

private:
    char * _pstr;
};

void test2(){
    String s2 = "hello";
    cout << s2[0] << endl;
    s2[0] = 'H';
    cout << s2[0] << endl;

    //遍历
    for(int i = 0; i < s2.size(); ++i){
        cout << s2[i] << " ";
    }
    cout << endl;
}

int main()
{
    test2();
    return 0;
}

