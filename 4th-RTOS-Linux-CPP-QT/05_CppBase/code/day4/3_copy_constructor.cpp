#include <iostream>
using std::cout;
using std::endl;
//拷贝构造函数形式探究
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    //2.const能否去掉呢？？？？
    //不建议去掉const，原因一可以修改右操作数 Point pt = pt2;
    //原因二是如果去掉将无法处理右值，临时对象的拷贝
    //Point pt = Point(1, 2);
    //形参和实参结合 Point & rhs = Point(1, 2);
    //非const引用只可以绑定左值，无法绑定右值
    //const引用既可以绑定左值，也可以绑定右值
    Point(const Point & rhs)
    :_x(rhs._x)
    ,_y(rhs._y)
    {
        //过河拆桥
        //rhs._x = 0;
        //rhs._y = 0;
        cout << "Point(const Point &)" << endl;
    }

    ~Point(){
        cout << "~Point()" << endl;
    }

    void print(){
        cout << _x << "," << _y << endl;
    }

private:
    int _x;
    int _y;
};


void test(){
    Point pt(1, 2);
    pt.print();
    Point pt2 = pt;
    Point pt3(pt);
    pt2.print();
    pt.print();
}

void test2(){
    //临时对象、右值对象
    Point pt = Point(1, 2);
}

void test3(){
    //什么叫左值，什么叫右值？？？？
    //左值是可以取地址的
    //右值是不可以取地址操作的，临时变量、临时对象
    //左值和右值还可以去记忆是否有名称
    //一般情况下有名称的是左值，没有名称的是右值(有例外)
    //“hello,world”字符串常量是左值，可以取地址的
    //引用、左值引用、右值引用(后续最后一个章节介绍到)
    //const引用
    int number = 10;
    cout << &number << endl;
    //左值引用：因为绑定的是一个左值，
    //同时它也是一个非const引用
    int & ref = number;
    //ref2是一个左值引用，只可以去绑定左值，无法绑定右值
    int & ref2 = 10;
    cout << &10 << endl;
    //左值，可以取地址的
    Point pt(1, 2);
    cout << &pt << endl;
    cout << &Point(1, 2) << endl;
    cout << &"hello" << endl;
    Point & refPoint = Point(1, 2);

    //const引用、非const引用
    const int & ref4 = number;
    const int & ref5 = 10;
    //const引用可以提升右操作数也就是右值的生命周期
    //直至到变量结束为止，会和refPoint2的生命周期保持一致
    const Point & refPoint2 = Point(1, 3);
}

int main()
{
    test();
    return 0;
}

