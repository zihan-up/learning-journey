#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//写时复制引用计数存放位置讨论
//int refcount = 0;
//可能此时有3个string指向了hello 两个指向了word
//上述的这种方式很难表示出这种关系
//hello
//world

class String{
public:
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }

    //拷贝构造
    //String s2 = s;
    //拷贝构造的const能否去掉呢？？？非常不建议
    //1.去掉const意味着可以任意修改有操作的值
    //2.没法去绑定临时对象的拷贝
    //String s2 = String("hello");
    String(const String & rhs)
    :_refcount(rhs._refcount + 1)
    ,_pstr(rhs._pstr)
    {
        ++rhs._refcount;
        int number = 10;
        //rhs._count = &number;
        //++*rhs._count;
    }
private:
    //这种方式可以吗？？？？
    int _refcount = 0;

    //这样是否可行？在const修饰的情况下，能不能顺利修改这个值
    //需要修改的值这个指针所指向的值
    int * _count;

    char * _pstr;
};

void test(){

}

int main()
{
    test();
    return 0;
}

