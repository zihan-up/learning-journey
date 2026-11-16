#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
using std::cerr;
//写时复制代码第二版

class CowString{
public:
    CowString()
    :_pstr(new char[1 + 4]() + 4)
    {
        //引用计数= 1
        *(int *)(_pstr - 4) = 1;
    }
    CowString(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1 + 4]() + 4)
    {
        strcpy(_pstr, pstr);
        *(int *)(_pstr - 4) = 1;

    }
    //拷贝构造
    CowString(const CowString & rhs)
    :_pstr(rhs._pstr)
    {
        //引用计数++
        ++*(int *)(_pstr - 4);
    }
    //赋值运算符函数
    //s1 = s2;s1的值会被s2替换
    CowString & operator=(const CowString & rhs){
        if(this != &rhs){
            //左操作数的引用计数-1
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

    int refcount() const{
        return *(int *)(_pstr - 4);
    }
    int size() const {
        return strlen(_pstr);
    }
    
private:
    class CharProxy{
    public:
        CharProxy(size_t index, CowString & s)
        :_index(index)
        ,_s(s)
        {

        }
        friend ostream & operator<<(ostream & os, const CowString::CharProxy & rhs);
        //类里面需要写哪些函数呢？？？？
        //1.实现赋值运算符
        //str[0](charProxy) = 'H';
        //最终_pstr的下标0位置需要改为H
        //把_pstr[_index]指定的这个位置的值改为c
        //依然是需要判断引用计数是否大于1
        //大于1：先进行深拷贝(原引用计数-1，现有引用计数=1)，再进行修改
        //等于1：直接修改即可
        //走这个赋值运算符的全部都是写，不会是读
        char & operator=(const char & c){
            if(_s.refcount() > 1){
                //引用计数 > 1
                char * temp = new char[strlen(_s._pstr) + 1 + 4]() + 4;
                strcpy(temp, _s._pstr);
                //原来的引用计数-1
                --*(int *)(_s._pstr - 4);
                //现有的引用计数=1
                _s._pstr = temp;
                *(int *)(_s._pstr - 4) = 1;
            }
            //引用计数=1
            _s._pstr[_index] = c;
            return _s._pstr[_index];
        }
        //2.实现输出流运算符
    private:
        size_t _index;
        CowString & _s;
    };
    friend ostream & operator<<(ostream & os, const CowString::CharProxy & rhs);
    friend ostream & operator<<(ostream & os, const CowString & rhs);
public:
    //下标访问运算符
    //返回的是一个类对象
    CharProxy operator[](size_t index){
        static CowString s;
        if(index >= size()){
            return CharProxy(0, s);
        }
       return CharProxy(index, *this); 
    }


private:
    char * _pstr;
};
//CowString s("hello");
// cout << str[0] << endl; 'h'
// 现在的问题是：str[0]是一个charProxy对象，但是最终使用输出流运算符
// 需要输出的是h
// 内部类需要访问外部类的数据成员_pstr，需要借助于对象去访问
// 但是最终显示的输出结果要求是一个字符
// 字符在哪？？？？外部类中
//针对CharProxy的输出流运算符
//1.该函数需要设置为CowString的友元
//2.该函数需要访问rhs的私有数据成员，所以需要设置为CharProxy的友元
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs){
    //分别对读还是写下标进行处理
    os << rhs._s._pstr[rhs._index];
    return os;
}
ostream & operator<<(ostream & os, const CowString & rhs){
    os << rhs._pstr;
    return os;
}


void test(){
    CowString s("hello");
    cout << s.refcount() << endl;
    cout << s[0] << endl;
    cout << s[2] << endl;
    cout << s.refcount() << endl;
}
void test2(){
    CowString s("hello");
    CowString s2 = s;
    cout << s.refcount() << endl;//2
    s[0] = 'H';
    cout << s.refcount() << endl;//1
    cout << s2.refcount() << endl;//1
    cout << s[0] << endl;//H
    cout << s2[0] << endl;// h
}
void test3(){
    CowString s("hello");
    cout << s[9] << endl;
    s[9] = 'o';
    cout << s[9] << endl;

}

int main()
{
    test3();
    return 0;
}

