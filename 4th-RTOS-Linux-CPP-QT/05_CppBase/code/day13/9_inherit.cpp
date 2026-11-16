#include <iostream>
using std::cout;
using std::endl;
//单继承语法特征
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

#if 0
    Point(){
        cout << "Point()" << endl;
    }
#endif

private:
    int _x;
    int _y;
};

class Point3D : public Point{
public:
    //会先调用Point3D构造函数
    //会先执行构造函数的初始化列表，会调用基类的构造函数
    //随后再去执行构造函数的函数体
    Point3D(int x, int y, int z)
    //:Point(x, y)
    //,_z(z)
    {
        cout << "Point3D(int,int,int)" << endl;
    }


private:
    int _z;
};
void test(){
    Point3D pt3d(1, 2, 3);
}

int main()
{
    test();
    return 0;
}

