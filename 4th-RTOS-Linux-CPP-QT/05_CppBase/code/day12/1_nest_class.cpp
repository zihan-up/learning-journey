#include <iostream>
using std::cout;
using std::endl;
//嵌套类
//外部类
class Line{
public:
    Line(int x1, int y1, int x2, int y2)
    :_pt1(x1, y1)
    ,_pt2(x2, y2)
    {
        cout << "Line(int,int,int,int)" << endl;
    }
    void printline(){
        _pt1.print();
        cout << "------>";
        _pt2.print();
        cout << endl;
    }
    friend void test();
    //内部类
private:
    class Point{
    public:
        Point(int x, int y)
        :_x(x)
        ,_y(y)
        {}
        void print(){
            cout << "(" << _x << "," << _y << ")";
        }
    private:
        int _x;
        int _y;
    };
private:
    Point _pt1;
    Point _pt2;

};
void test(){
    //创建一个line对象，调用printline函数
    //Line是一个外部类对象，全局类对象
    Line line(1, 2, 3, 4);
    line.printline();
    //但是如果此时希望创建一个Point类对象，注意：
    //Point pt1(1, 2);error
    //内部类对象的创建需要使用外部类+作用域限定符的方式
    //如果Point位于私有区域，那么我们需要访问Line里面的
    //私有内部类Point
    //必须得将当前test函数设置为Line的友元
    Line::Point pt1(1, 2);
}

void test2(){
    cout << sizeof(Line) << endl;
}

void test3(){
    Line line(1, 2, 3, 4);
    cout << line << endl;
}

int main()
{
    test2();
    return 0;
}

