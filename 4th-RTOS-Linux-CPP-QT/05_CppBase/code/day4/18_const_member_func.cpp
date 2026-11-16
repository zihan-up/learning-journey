#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    //const成员函数
    //此时二者是可以共存的
    //说明了啥？？？
    //下面这两个函数形成了函数重载
    //函数重载形成的条件:参数的类型、参数的个数、参数的顺序
    //成员函数实际上有一个隐形的参数 this指针
    //this指针不同
    //const成员函数中的this指针：
    //既不可以变更指向，也不可以通过指针去修改所指向的值
    //const Point * const this
    void print() const {
        Point pt;
        //this = &pt;
        //this->_x = 0;
        //this->_y = 0;
    }
    //对于this指针来说，可以通过指针去修改所指向的值
    //Point * const this
    void print(){
        this->_x = 0;
        this->_y = 0;
    }
#if 0
    const 成员函数和普通的成员函数可以形成重载，主要在于
        编译器处理过之后的形参不同
        void print(const Point * const this){

        }
        void print(Point * const this){

        }
#endif


private:
    int _x;
    int _y;
};
//设计一个String类，用来进行字符串的操作
//希望能够减少内存的操作
//对于使用者来说，可以将内置数据类型一样去使用
//直接调用一些简单的函数便可以完成字符串的各种操作
class String{
public:
    String(const char * pstr)
    :_pstr()
    {

    }
    //可以将两个字符串进行拼接操作
    String & append(const char * pstr){

    }

    //可以显示当前字符串的长度
    int size() const{
        return strlen(_pstr);
    }

private:
    char * _pstr;
};

void test(){
    String s1("hello");
    s1.append("world");

}

int main()
{
    test();
    return 0;
}

