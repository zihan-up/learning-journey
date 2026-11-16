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
    :_pt1(x1, y1)
    ,_pt2(x2, y2)
    {
        cout << "Line(int,int,int,int)" << endl;
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

