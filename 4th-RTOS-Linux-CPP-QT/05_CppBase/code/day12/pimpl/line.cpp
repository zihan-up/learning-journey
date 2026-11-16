#include "line.h"
#include <iostream>
using namespace std;
//在该文件中去做对应的实现
//line.h只有头文件的声明，具体的实现细节没有的
//通过头文件得知：
//1.Line里面有一个私有内部类LineImpl
//2.Line中持有一个指针数据成员_impl
//3.没有Point的任何说明，希望将Point放置在LineImpl内部类中
class Line::LineImpl{
public:
    //参数需要传递给Point
    LineImpl(int x1, int y1, int x2, int y2)
    :_pt1(x1, y1)
    ,_pt2(x2, y2)
    {
        cout << "LineImpl(int,int,int,int)" << endl;
    }

    void printLine(){
        _pt1.print();
        cout << "-------->";
        _pt2.print();
        cout << endl;
    }

    class Point{
    public:
        Point(int x, int y)
        :_x(x)
        ,_y(y)
        {

        }
        void print(){
            cout << "(" << _x << "," << _y << ")" << endl;
        }

    private:
        int _x;
        int _y;
    };
private:
    Point _pt1;
    Point _pt2;
};

//构造函数中指针数据成员申请了堆空间
Line::Line(int x1, int y1, int x2, int y2)
:_impl(new LineImpl(x1, y1, x2, y2))
{
    cout << "Line(int,int,int,int)" << endl;
}
//析构函数中指针数据成员需要回收堆空间
Line::~Line(){
    if(_impl){
        delete _impl;
        _impl = nullptr;
    }
}
void Line::printLine(){
    _impl->printLine();
}
