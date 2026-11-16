#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {
    }

    void func(){
        cout << "Point::func()" << endl;
    }

    void print(){
        cout << _x << "," << _y << endl;
    }

private:
    int _x;
    int _y;
};


void test(){
    Point * pt = nullptr;
    //func函数位于程序代码区，调用它并不需要额外的一些限制
    //pt->func()经过编译器处理过后 func(pt);
    //p.print()经过编译器处理过后 func(&p);
    //调用成员函数依然是可以正常调用的，只不过此时传递进去的this指针的值
    //为nullptr
    //如果需要去访问数据成员、那么会出问题
    pt->func();
    pt->print();
}

int main()
{
    test();
    return 0;
}

