#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

class CowString{
public:
    //_pstr = new char[5]();指向的依然是首地址
    //但是前4字节是用来去存储引用计数数字的
    //字符串永远不会使用到
    //为了处理字符串方便，我们将_pstr指向到后移4字节
    CowString()
    :_pstr(new char[1 + 4]() + 4)
    {
        ++*(int *)(_pstr - 4);
    }

    CowString(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1 + 4]() + 4)
    {
        //直接进行strcpy的操作
        strcpy(_pstr, pstr);
        ++*(int *)(_pstr - 4);
    }

    //拷贝构造函数
    //1.浅拷贝
    //2.引用计数 + 1
    CowString(const CowString & rhs)
    :_pstr(rhs._pstr)
    {
        //_pstr指向向前移动4字节
        //强转成int *
        //解引用操作 ++
        ++*(int *)(_pstr - 4);
    }

    //赋值运算符函数
    //1.自赋值判断
    //2.左操作数的引用计数 - 1；-1之后如果为0，需要回收堆空间
    //指向右操作数申请的堆空间，也就是浅拷贝
    //3.右操作数的引用计数 + 1
    //4.返回对象
    CowString & operator=(const CowString & rhs){
        if(this != &rhs){
           if(--*(int *)(_pstr - 4) == 0){
                delete [] (_pstr - 4);
            }
            _pstr = rhs._pstr;
            ++*(int *)(_pstr - 4);
        }
        return *this;
    }

    //析构函数
    ~CowString(){
        if(--*(int *)(_pstr - 4) == 0){
            delete [] (_pstr - 4);
        }
    }

    //将引用计数暴露出去
    int refcount() const{
        return *(int *)(_pstr - 4);
    }
    int size() const {
        return strlen(_pstr);
    }
    const char * c_str() const{
        return _pstr;
    }

    //写
    //CowString s1("hello");
    //s1[0] = 'H';
    //CowString s1 = s2;
    //s1[0] = 'H';
    //分析此时的引用计数大于1还是等于1
    //如果等于1：直接修改即可
    //如果大于1：执行深拷贝，原先的引用计数-1，现有的引用计数=1，
    //再去修改
    char & operator[](size_t index){
        if(index >= size()){
            static char nullchar = '\0';
            return nullchar;
        }
        if(*(int *)(_pstr - 4) > 1){
            //先申请一个临时的堆空间，复制字符串的内容
            char * temp = new char[strlen(_pstr) + 1 + 4]() + 4;
            strcpy(temp, _pstr);
            //将原先指向的堆空间的引用计数-1
            --*(int *)(_pstr - 4);
            _pstr = temp;
            //变更指向之后，现有的引用计数=1
            *(int *)(_pstr - 4) = 1;
        }
        return _pstr[index];
    }
    char & operator[](size_t index) const{
        if(index >= size()){
            static char nullchar = '\0';
            return nullchar;
        }
        return _pstr[index];
    }
    friend ostream & operator<<(ostream & os, const CowString & rhs);


private:
    char * _pstr;
};
//输出流运算符
ostream & operator<<(ostream & os, const CowString & rhs){
    os << rhs._pstr;
    return os;
}


class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {}

private:
    int _x;
    int _y;
};

void test(){
    Point pt(1, 2);
    Point * p = &pt;
    //cout <<sizeof(Point) << endl;
    int * pInt = (int *)p;
    cout << *pInt << endl;
    cout << *(pInt + 1) << endl;
}
void test2(){
    CowString s("hello");
    cout << s.refcount() << endl;
    CowString s2 = s;
    cout << s.refcount() << endl;
    cout << s2.refcount() << endl;
} 
void test3(){
    CowString s1("hello");
    CowString s2("world");
    CowString s3 = s1;
    cout << s1.refcount() << endl;
    cout << s3.refcount() << endl;
    cout << s2.refcount() << endl;
    // s1 s3 2     s2 1
    s1 = s2;
    cout << s1.refcount() << endl;//2
    cout << s3.refcount() << endl; //1
    cout << s2.refcount() << endl;//2
    s3 = s2;
    cout << s1.refcount() << endl;
    cout << s3.refcount() << endl; //1
    cout << s2.refcount() << endl;
}

void test4(){
    CowString s1("hello");
    cout << s1.refcount() << endl;
    cout << s1 << endl;
    s1[0] = 'H';
    cout << s1.refcount() << endl;
    cout << s1 << endl;
}
void test5(){
    CowString s1("hello");
    CowString s2 = s1;
    cout << s1.refcount() << ":" << s2.refcount() << endl;
    cout << s1 << ":" << s2 << endl;
    s2[0] = 'H';
    cout << s1.refcount() << ":" << s2.refcount() << endl;
    cout << s1 << ":" << s2 << endl;
}
//演示有问题的代码
//对于内置数据来说，没法区分读还是写
//但是如果是一个自定义类型类对象，能否区分读还是写？？？？？
//s2[0]其实是一个char
//s2[0]是一个CharProxy对象，能否区分读还是写？？？？
//cout << s2[0] =========> cout << charProxy << endl;输出流运算符
//s2[0] = 'H' ============> charProxy = 'H'; 赋值运算符
void test6(){
    //读操作，不写
    CowString s1("hello");
    CowString s2 = s1;
    cout << s1.refcount() << ":" << s2.refcount() << endl;
    cout << s2[0] << endl;
    cout << s1.refcount() << ":" << s2.refcount() << endl;
}

int main()
{
    test6();
    return 0;
}

