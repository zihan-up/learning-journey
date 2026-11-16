#include <iostream>
using std::cout;
using std::endl;
//拷贝构造函数的调用时机
//1.使用一个已经存在的对象去创建一个新的对象
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    Point(const Point & rhs)
    :_x(rhs._x)
    ,_y(rhs._y)
    {
        cout << "Point(const Point &)" << endl;
    }

    ~Point(){
        cout << "~Point()" << endl;
    }

    void print(){
        cout << _x << "," << _y << endl;
    }

private:
    int _x;
    int _y;
};

Point func(){
    Point pt(1, 2);
    return pt;
}


void test(){
    Point pt2 = func();
    cout << "test()函数执行结束" << endl;
}

int main()
{
    test();
    return 0;
}

