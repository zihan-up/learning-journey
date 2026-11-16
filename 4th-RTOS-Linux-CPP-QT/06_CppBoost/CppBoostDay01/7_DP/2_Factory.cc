#include <math.h>
#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;

class Figure
{
public:
    //纯虚函数
    virtual void display() const = 0;
    virtual double area() const = 0;

    //将基类的析构函数设置为虚函数
    virtual ~Figure(){ cout << "~Figure()"  << endl;}
};

class Rectangle
: public Figure
{
public:
    Rectangle(double length = 0, double width = 0)
    : _length(length)
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
        return _length * _width;
    }

    ~Rectangle()
    {
        cout << "~Rectangle()" << endl;
    }
private:
    double _length;
    double _width;
};

class Circle
: public Figure
{
public:
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
        return 3.14 * _radius *_radius;;
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
        cout << "Triangle";
    }

    double area() const override
    {
        //海伦公式
        double tmp = (_a + _b + _c)/2;

        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp - _c));
    }

    ~Triangle()
    {
        cout << "~Triangle()" << endl;
    }
private:
    double _a;
    double _b;
    double _c;
};

void func(Figure *pfig)
{
    pfig->display();
    cout << "的面积 : " << pfig->area() << endl;
}


//工厂方法：工厂设计模式
//优点：
//1、满足了单一职责原则
//2、满足了开放闭合原则
//3、满足了依赖倒置原则
//4、满足了里氏替换原则
//
//缺点：
//工厂的数目会随着产品的数目而急剧上升

class Factory
{
public:
    virtual Figure *create() = 0;
    virtual ~Factory(){}
};

class RectangleFactory
: public Factory
{
public:
    virtual Figure *create() override
    {
        //读取配置文件，然后获取长方形的长与宽
        //...
        Rectangle *prec = new  Rectangle(10, 20);
        return prec;
    }
};

class CircleFactory
: public Factory
{
public:
    virtual Figure *create() override
    {
        //读取配置文件，然后获取半径
        //...
        Circle *pcir = new Circle(10);
        return pcir;
    }
};

class TriangleFactory
: public Factory
{
public:
    virtual Figure *create() override
    {
        //读取配置文件，然后获取三角形的三个边
        //...
        Triangle *ptri = new Triangle(3, 4, 5);
        return ptri;
    }
};

int main(int argc, char **argv)
{
    //长方形
    unique_ptr<Factory> recFac(new RectangleFactory());
    unique_ptr<Figure> prec(recFac->create()); 
    //圆形形
    unique_ptr<Factory> cirFac(new CircleFactory());
    unique_ptr<Figure> pcir(cirFac->create()); 
    //三角形
    unique_ptr<Factory> triFac(new TriangleFactory());
    unique_ptr<Figure> ptri(triFac->create()); 

    func(prec.get());
    func(pcir.get());
    func(ptri.get());

    return 0;
}

