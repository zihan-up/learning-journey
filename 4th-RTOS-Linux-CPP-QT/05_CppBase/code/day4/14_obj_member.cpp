#include <iostream>
using std::cout;
using std::endl;
//对象成员
//有一个Point类，还有一个Line类
//Line类中需要持有两个Point对象成员才可以形成一个有效的line对象
class Point{
public:
    Point(int x, int y)
    :_x(x)//表示的是用x给_x进行初始化操作
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
    Point(){
        cout << "Point()" << endl;
    }
    ~Point(){
        cout << "~Point()" << endl;
    }
    Point(const Point & rhs)
    :_x(rhs._x)
    ,_y(rhs._y)
    {
        cout << "Point(const Point &)" << endl;
    }
    void print(){
        cout << "(" << _x << "," << _y << ")";
    }

private:
    int _x;
    int _y;
};
class Line{
public:
    //关于对象数据成员的初始化，还可以使用另外一种形式
    //构造函数的额形参pt1和pt2和实参结合的时候各有1次(2次)
    Line(Point & pt1, Point & pt2)
    :_pt1(pt1)//使用pt1给_pt1初始化也需要1次
    ,_pt2(pt2)
    {
        cout << "Line(Point,Point)" << endl;
    }
    ~Line(){
        cout << "~Line()" << endl;
    }

    void print(){
        _pt1.print();
        cout << "------->";
        _pt2.print();
        cout << endl;
    }

private:
    //对象数据成员一定会被初始化
    //优先根据我们在初始化列表中设定的值进行初始化
    //如果没有上一步，则会调用对象数据成员的无参构造函数进行初始化
    //如果这一步也没有，则直接出错
    Point & _pt1;
    Point & _pt2;
};


void test(){
    Point pt1(1, 2), pt2(3, 4);
    Line line(pt1, pt2);
    line.print();
}

int main()
{
    test();
    return 0;
}

