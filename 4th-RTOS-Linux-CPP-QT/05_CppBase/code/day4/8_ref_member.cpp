#include <iostream>
using std::cout;
using std::endl;
//引用数据成员
//引用一旦和某个变量绑定了之后，就可以再绑定到其他的变量
//在使用引用的时候，一定要注意，不要绑定到一个局部变量的引用
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    ,_z(_x)
    {

    }

    //这种写法有问题，_z的值不固定，为什么呢？？？？
    //_z 绑定的是z形参
    //一旦构造函数执行完毕之后，z便会被销毁
    //绑定的这块区域就是属于一个未知的区域
    //其实就是属于未定义行为
    Point(int x, int y, int z)
    :_x(x)
    ,_y(y)
    ,_z(z)
    {

    }
    void print(){
        cout << _x << "," << _y << "," << _z << endl;
    }


private:
    int _x;
    int _y;
    int & _z;
};


void test(){
    Point pt1(1, 2);
    pt1.print();
    Point pt2(1, 2, 3);
    pt2.print();
}

int main()
{
    test();
    return 0;
}

