#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

//抽象类
class Figure
{
public:
    //声明了两个纯虚函数
    virtual
    void display() const = 0;//打印图形的名字

    virtual 
    double area() const = 0;//计算图形的面积
};

class Rectangle
: public Figure
{
public:
    Rectangle(double len = 0, double width = 0)
    : _len(len)
    , _width(width)
    {
        cout << "Rectangle(double = 0, double = 0)" << endl;
    }

    void display() const override
    {
        cout << "Rectangle";
    }

    double area() const override
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
: public Figure
{
public:
    explicit
    Circle(double radius = 0)
    : _radius(radius)
    {
        cout << "Circle(double = 0)" << endl;
    }

    void display() const override
    {
        cout << "Circle";
    }

    double area() const override
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
: public Figure
{
public:
    Triangle(double a = 0, double b = 0, double c = 0)
    : _a(a)
    , _b(b)
    , _c(c)
    {
        cout << "Triangle(double = 0, double = 0, double = 0)" << endl;
    }

    void display() const override
    {
        cout << "Triangle" ;
    }

    double area() const override
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
    ref.display();
    cout << "'s 的面积 " << ref.area() << endl;
}

int main(int argc, char **argv)
{
    Rectangle rec(10, 20);
    Circle cir(10);
    Triangle tri(3, 4, 5);

    func(rec);
    func(cir);
    func(tri);

    return 0;
}


