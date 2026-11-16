#include <math.h>
#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;

//面向对象的设计原则：开放闭合原则
//对扩展开放，对修改关闭
//
//抽象类，作为接口使用
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


//简单工厂（静态工厂）：根据产品的名字去生产对应的产品
//特点：非常的简单
//缺点：
//1、违反了单一职责原则
//2、违反了开放闭合原则
//3、违反了依赖倒置原则
class Factory
{
public:
    static Figure *create(const string &name)
    {
        if(name == "rectangle")
        {
            //读取配置文件，然后获取长方形的长与宽
            //...
            Rectangle *prec = new  Rectangle(10, 20);
            return prec;
        }
        else if(name == "circle")
        {
            //读取配置文件，然后获取半径
            //...
            Circle *pcir = new Circle(10);
            return pcir;
        }
        else if(name == "triangle")
        {
            //读取配置文件，然后获取三角形的三个边
            //...
            Triangle *ptri = new Triangle(3, 4, 5);
            return ptri;
        }
        else if(name == "xxx")
        {

        }
        else if(name == "yyy")
        {

        }
        else
        {
            return nullptr;
        }
    }
#if 0
    static Figure *createRectangle()
    {
        //读取配置文件，然后获取长方形的长与宽
        //...
        Rectangle *prec = new  Rectangle(10, 20);
        return prec;
    }
    
    static Figure *createCircle()
    {
        //读取配置文件，然后获取半径
        //...
        Circle *pcir = new Circle(10);
        return pcir;
    }
    
    static Figure *createTriangle()
    {
        //读取配置文件，然后获取三角形的三个边
        //...
        Triangle *ptri = new Triangle(3, 4, 5);
        return ptri;
    }
#endif
};

#if 0
Figure *createRectangle()
{
    //读取配置文件，然后获取长方形的长与宽
    //...
    Rectangle *prec = new  Rectangle(10, 20);
    return prec;
}

Figure *createCircle()
{
    //读取配置文件，然后获取半径
    //...
    Circle *pcir = new Circle(10);
    return pcir;

}

Figure *createTriangle()
{
    //读取配置文件，然后获取三角形的三个边
    //...
    Triangle *ptri = new Triangle(3, 4, 5);
    return ptri;
}

#endif
int main(int argc, char **argv)
{
    unique_ptr<Figure> prec(Factory::create("rectangle"));
    unique_ptr<Figure> pcir(Factory::create("circle"));
    unique_ptr<Figure> ptri(Factory::create("triangle"));

    func(prec.get());
    func(pcir.get());
    func(ptri.get());

    return 0;
}

