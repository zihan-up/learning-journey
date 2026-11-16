#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    //explicit
    Point(int x = 0, int y = 0)
    :_x(x)
    ,_y(y)
    {
    }

    void func(){
        cout << "Point::func()" << endl;
    }

    void print(){
        cout << _x << "," << _y << endl;
    }

private:
    int _x;
    int _y;
};


void test(){
    Point pt = 5;
}

int main()
{
    test();
    return 0;
}

