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
    void print(){
        cout << "(" << _x << "," << _y << ")";
    }

private:
    int _x;
    int _y;
};
class Line{
public:
    Line(int x1, int y1, int x2, int y2)
    :_pt1(x1, y1)//表示的是会借助于x1,y1给_pt1进行初始化，但是
                 //必须得调用构造函数
    ,_pt2(x2, y2)
    {

    }

    void print(){
        _pt1.print();
        cout << "------->";
        _pt2.print();
        cout << endl;
    }

private:
    Point _pt1;
    Point _pt2;
};


void test(){
    //Point pt(1, 2);
    Line line(1, 2, 3, 4);
    line.print();
}

int main()
{
    test();
    return 0;
}

