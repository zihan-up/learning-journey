#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//RAII思想落地实现：
template <class T>
class RAII{
public:
    //构造函数中托管资源
    //析构函数中释放资源
    RAII(T * p)
    :_data(p)
    {}

    RAII(){}

    //除了FILE等特殊类型的指针不能处理之外，其他都是可以处理的
    ~RAII(){
        if(_data){
            delete _data;
            _data = nullptr;
        }
    }

    //不允许进行复制或者赋值操作
    RAII(const RAII & rhs) = delete;
    RAII & operator=(const RAII & rhs) = delete;

    //提供若干访问资源的方法
    T * get(){
        return _data;
    }

    //直接在RAII对象中直接操作指针呢？？？
    //重载箭头、解引用运算符
    T * operator->(){
        return _data;
    }

    T & operator*(){
        return *_data;
    }


private:
    T * _data;
};

class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {}

    void print(){
        cout << _x << "," << _y << endl;
    }

private:
    int _x;
    int _y;
};

class String{
public:
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }
    ~String(){
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr;
        }
    }

    const char * c_str() const{
        return _pstr;
    }

private:
    char * _pstr;
};


void test(){
    //现在再使用指针去指向位于堆区的资源时，
    //还需要考虑释放的问题嘛？
    //还需要考虑资源回收、内存泄漏的问题嘛？？？？
    //如果不用考虑，能否称之为是智能指针呢？？？
    RAII<Point> raii(new Point(1, 2));
    raii->print();
    //RAII<Point> raii2 = raii;error无法调用拷贝构造函数
    RAII<String> raii2(new String("hello"));
    cout << raii2->c_str() << endl;
}

void test2(){
    //但是使用的时候也不是百无禁忌
    //不可以将一个原生的指针交给两个raii同时进行管理
    Point * pt = new Point(1, 2);
    RAII<Point> raii(pt);
    RAII<Point> raii2(pt);

}

int main()
{
    test2();
    return 0;
}

