#include <math.h>
#include <iostream>
using std::cout;
using std::endl;
//友元之普通函数的形式
//编写一个普通的函数，去求解两个点之间的距离
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {

    }
    //函数设置为当前类的友元
    friend float distance(const Point & pt1, const Point & pt2);

private:
    int _x;
    int _y;
};

//普通的函数
//将当前这个函数声明为Point类的友元
float distance(const Point & pt1, const Point & pt2){
    float result = pow(pt1._x - pt2._x, 2) + pow(pt1._y - pt2._y,2);
    return sqrt(result);
 }
void test(){
    Point pt1(0, 3), pt2(3, 7);
    cout << distance(pt1, pt2) << endl;
}

int main()
{
    test();
    return 0;
}

