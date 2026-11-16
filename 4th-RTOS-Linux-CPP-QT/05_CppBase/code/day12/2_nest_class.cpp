#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
//嵌套类输出流运算符重载
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
    friend ostream & operator<<(ostream & os, const Line & rhs);

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
        friend ostream & operator<<(ostream & os, const Line::Point & rhs);
    private:
        int _x;
        int _y;
    };
    friend ostream & operator<<(ostream & os, const Line::Point & rhs);
private:
    Point _pt1;
    Point _pt2;

};
//1.该函数需要设置为Point的友元，因为需要访问的Point的私有数据成员_x _y
//2.设置过后Line::Point显示有问题？为什么？？
//因为Point位于私有区域
//需要将该函数还设置为Line的友元
ostream & operator<<(ostream & os, const Line::Point & rhs){
    os << "(" << rhs._x << "," << rhs._y << ")";
    return os;
}
//1.该函数需要设置为Line的友元，因为需要访问Line的私有数据成员_pt1
//2.设置了之后依然报错，原因在于os << Line::point没有对应的函数
//此时需要做的事情是实现对于Point的输出流运算符函数的重载
ostream & operator<<(ostream & os, const Line & rhs){
    os << rhs._pt1;
    cout << "------->";
    os << rhs._pt2;
    return os;
}


void test3(){
    Line line(1, 2, 3, 4);
    cout << line << endl;
}

int main()
{
    test3();
    return 0;
}

