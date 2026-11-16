#include <math.h>
#include <iostream>
using std::cout;
using std::endl;
//友元之成员函数的形式
//此时需求进一步改变，distance函数不再是一个普通的函数，而是Line类里面的成员函数
//此时需要去求解两个Point之间的距离
//前向声明仅仅只是能够认识这个符号，置于这个类中究竟有哪些函数、哪些数据成员
//那么是无法通过前向声明得知的
class Point;
class Line{
public:
    float distance(const Point & pt1, const Point & pt2);
};

class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {

    }
    friend float Line::distance(const Point & pt1, const Point & pt2);
private:
    int _x;
    int _y;
};
    
float Line::distance(const Point & pt1, const Point & pt2){
    float result = pow(pt1._x - pt2._x, 2) + pow(pt1._y - pt2._y,2);
    return sqrt(result);
}

void test(){
    Point pt1(0, 3), pt2(3, 7);
    Line line;
    cout << line.distance(pt1, pt2) << endl;
}

int main()
{
    test();
    return 0;
}

