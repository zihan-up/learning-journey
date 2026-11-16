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
    int getX() const{
        return _x;
    }
    int getY() const{
        return _y;
    }

private:
    int _x;
    int _y;
};

//普通的函数
//如果不借助于友元，此时可以主动提供一个公有的get方法
//将_x和_y暴露出来
float distance(const Point & pt1, const Point & pt2){
    float result = pow((pt1.getX() - pt2.getX()), 2) + pow((pt1.getY() - pt2.getY()),2);
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

