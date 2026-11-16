#include <iostream>
using std::cout;
using std::endl;
//现在需要设计一类不可以变更的坐标系的点
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {
        //_x = x;error 
        //_y = y;error
    }


private:
    const int _x;
    const int _y;
};


void test(){

}

int main()
{
    test();
    return 0;
}

