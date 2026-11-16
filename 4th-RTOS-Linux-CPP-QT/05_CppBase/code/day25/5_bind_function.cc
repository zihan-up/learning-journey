#include <math.h>
#include <iostream>
#include <functional>
#include <string>

using std::cout;
using std::endl;
using std::bind;
using std::function;
using std::string;

//Q1：左值与右值？取地址
//A:左值是可以取地址的，右值是不能取地址的；
//
//Q2：左值引用与右值引用？
//A:左值引用可以绑定到左值，不能绑定到右值；
//右值引用可以绑定到右值，不能绑定到左值；
//const左值引用既可以绑定左值也可以绑定右值
//int a = 10;
//const int &ref = 10;
//const int &ref2 = a;
//int &&rref = 10;

//Q3:左值引用到底是左值还是右值
//右值引用到底是左值还是右值
//
void test()
{
    string s1("hello");
    &s1;//左值
    string("hello");//右值
    &"hello";//左值
}

#if 0
class String
{
String &operator=(String &&rhs)
{
    if(this != &rhs)
    {

    }
}
};
#endif

//面向对象的写法：纯虚函数（函数） + 继承
//基于对象的写法: std::bind + std::function
//
//回调函数的注册与执行的思路在C语言中借助的是函数指针；
//但是在C++中借用的是std::bind + std::function
class Figure
{
public:
    using DisplayCallback = function<void()>;
    using AreaCallback = function<double()>;

    //数据成员赋值
    //能明确的知道传递进来的就是右值的话
    void setDisplayCallback(DisplayCallback &&cb)
    {
        _displayCallback = std::move(cb);
    }

    void setAreaCallback(AreaCallback &&cb)
    {
        _areaCallback = std::move(cb);
    }

    void handleDisplayCallback() const
    {
        if(_displayCallback)
        {
            _displayCallback();
        }
    }

    //将两个数据成员进行执行
    double handleAreaCallback() const
    {
        if(_areaCallback)
        {
            return _areaCallback();
        }
        else
        {
            return 0.0;
        }
    }

private:
    DisplayCallback _displayCallback;//子对象
    AreaCallback _areaCallback;//子对象
};

class Rectangle
{
public:
    Rectangle(double len = 0, double width = 0)
    : _len(len)
    , _width(width)
    {
        cout << "Rectangle(double = 0, double = 0)" << endl;
    }

    void display(int x) const 
    {
        cout << "Rectangle";
    }

    double area() const 
    {
        return _len * _width;
    }

    ~Rectangle()
    {
        cout << "~Rectangle()" << endl;
    }

private:
    double _len;
    double _width;

};

//Circle c1 = 10;//int ===>Circle
class Circle
{
public:
    explicit
    Circle(double radius = 0)
    : _radius(radius)
    {
        cout << "Circle(double = 0)" << endl;
    }

    void print() const 
    {
        cout << "Circle";
    }

    double printArea() const 
    {
        return 3.14 * _radius * _radius;
    }

    ~Circle()
    {
        cout << "~Circle()" << endl;
    }
private:
    double _radius;
};

class Triangle
{
public:
    Triangle(double a = 0, double b = 0, double c = 0)
    : _a(a)
    , _b(b)
    , _c(c)
    {
        cout << "Triangle(double = 0, double = 0, double = 0)" << endl;
    }

    void show() const 
    {
        cout << "Triangle" ;
    }

    double showArea() const 
    {
        double tmp = (_a + _b + _c)/2;
        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp -_c));
    }

    ~Triangle()
    {
        cout <<"~Triangle()" << endl;
    }
private:
    double _a;
    double _b;
    double _c;
};

void func(const Figure &ref)
{
    ref.handleDisplayCallback();
    cout << "'s 的面积 " << ref.handleAreaCallback() << endl;
}

int main(int argc, char **argv)
{
    Rectangle rec(10, 20);
    Circle cir(10);
    Triangle tri(3, 4, 5);

    Figure fig;
    /* function<void()> f = bind(&Rectangle::display, &rec, 1); */
    /* fig.setDisplayCallback(std::move(f)); */
    fig.setDisplayCallback(bind(&Rectangle::display, &rec, 1));
    fig.setAreaCallback(bind(&Rectangle::area, &rec));
    func(fig);

    fig.setDisplayCallback(bind(&Circle::print, &cir));
    fig.setAreaCallback(bind(&Circle::printArea, &cir));
    func(fig);

    fig.setDisplayCallback(bind(&Triangle::show, &tri));
    fig.setAreaCallback(bind(&Triangle::showArea, &tri));
    func(fig);

    return 0;
}


