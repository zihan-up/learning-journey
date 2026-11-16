#include <iostream>
using std::cout;
using std::endl;
//二维平面上面的点，进一步扩展到三维平面
//三种继承方式之间的区别分析
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {}
public:
    int _a;
protected:
    int _b;

private:
//protected:
    int _x;
    int _y;
};
//父类的私有数据成员，虽然可以被子类所继承，但是并不能够直接使用
//父亲有一个加密的保险箱，但是儿子并不知道密码
class Point3D : private Point{
public:
    //但是并不意味着父类就一定得需要设置protected，子类才可以使用
    Point3D(int x, int y, int z)
    :Point(x, y)
    ,_z(z)
    {

    }
    //在子类中去访问父类中不同修饰符的数据成员
    //对于公有继承，
    //子类内部可以访问
    //除了私有数据成员之外的其他数据成员
    void func(){
        cout << _a << endl;
        cout << _b << endl;
        cout << _x << endl;
    }

private:
    int _z;
};
class Point4D : public Point3D{
public:
    void func(){
        cout << _a << endl;
        cout << _b << endl;
    }

};
//私有继承：
    //子类内部可以访问
    //除了私有数据成员之外的其他数据成员
//在外部程序中
//无法通过子类访问到任何的数据成员
void test(){
    Point3D pt3d(1, 2, 3);
    cout << pt3d._a << endl;
    cout << pt3d._b << endl;
    cout << pt3d._x << endl;
}

int main()
{
    test();
    return 0;
}

