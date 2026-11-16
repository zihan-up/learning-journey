#include <iostream>
using std::cout;
using std::endl;
//二维平面上面的点，进一步扩展到三维平面
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {}

private:
//protected:
    int _x;
    int _y;
};
//父类的私有数据成员，虽然可以被子类所继承，但是并不能够直接使用
//父亲有一个加密的保险箱，但是儿子并不知道密码
class Point3D : public Point{
public:
    //但是并不意味着父类就一定得需要设置protected，子类才可以使用
    Point3D(int x, int y, int z)
    :Point(x, y)
    ,_z(z)
    {

    }

    void func(){
         //cout << _x << _y << _z << endl;error 
    }

private:
    int _z;
};

void test(){

}

int main()
{
    test();
    return 0;
}

