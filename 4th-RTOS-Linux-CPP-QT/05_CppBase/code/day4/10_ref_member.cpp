#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y, const int & z)
    :_x(x)
    ,_y(y)
    ,_z(z)
    {

    }
    void print(){
        cout << _x << ":" << _y << ":" << _z << endl;
    }


private:
    int _x;
    int _y;
    const int & _z;
};

void test(){
    Point pt(1, 2, 3);
   // int z = 3;
    //Point pt(1, 2, z);//这种方式是可行的
    pt.print();
}

int main()
{
    test();
    return 0;
}

