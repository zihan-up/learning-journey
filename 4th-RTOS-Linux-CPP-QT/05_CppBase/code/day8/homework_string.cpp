#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//帮助大家了解string底层的原理
//本质其实就是对于char *的封装
class String{
public:
    //即便是空字符串，那么我们也是申请了1字节的空间
    //好处是后续进行赋值运算符时，不需要考虑左操作数有没有申请堆空间的问题
    String()
    :_pstr(new char[1]())
    {
        cout << "String()" << endl;
    }
    //explicit 禁止隐式类型转换
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
        cout << "String(const char *)" << endl;
    }
    //利用目前已经存在的一个String对象创建一个新的String对象
    String(const String & rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
        cout << "String(const String & rhs)" << endl;
    }

    //将一个String对象的数据赋值给另外一个String对象
    String & operator=(const String & rhs){
        //自赋值的判断
        cout << "operator=(const String &)" << endl;
        if(this != &rhs){
            //回收左操作数申请的堆空间
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }
    ~String(){
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr;
        }
    }

    bool empty() const{
        return strlen(_pstr) == 0;
    }

    int size() const{
        return strlen(_pstr);
    }
    const char * c_str() const{
        return _pstr;
    }
    const char * data() const{
        return _pstr;
    }

    //s1.append(s2);
    //hello   world------>helloworld
    //该函数类似于 +=操作
    //1.先申请一块堆空间，使用一个临时的指针变量temp指向该堆空间
    //2.在这块堆空间中，需要执行字符串的拼接操作
    //3.回收函数调用者原先申请的堆空间
    //4.指针去指向刚刚新申请的这块堆空间
    String & append(String & rhs){
        if(rhs.size() != 0){
            char * temp = new char[strlen(_pstr) + strlen(rhs._pstr) + 1]();
            strcpy(temp, _pstr);
            strcat(temp, rhs._pstr);
            //3.
            delete [] _pstr;
            //4.
            _pstr = temp;
        }
        return *this;
    }

    //调用上面的函数即可
    String & append(const char * pstr){
        String temp(pstr);
        return append(temp);
    }
private:
    char * _pstr;
};

void test(){
    String s = "hello";
    String s2("hello");
    //s2.append("world");
    //随后s2便变成了helloworld
    String s3;
    s3 = s;
}

void test2(){
    String s = "hello";
    String s2 = s;
    cout << s2.c_str() << endl;
    String s3 = "world";
    cout << s3.c_str() << endl;
    s3 = s;
    cout << s3.c_str() << endl;

    //没有针对输出流运算符进行重载，解析不了String类型
    //cout << s3 << endl;
}

void test3(){
    String s = "hello";
    String s2 = "world";
    s.append(s2);
    cout << s.c_str() << endl;
    String s3;
    s2.append(s3);
    cout << s2.c_str() << endl;
}

void test4(){
    String s = "hello";
    s.append("world");
    cout << s.c_str() << endl;
}

int main()
{
    test4();
    return 0;
}

