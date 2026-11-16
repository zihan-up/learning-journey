#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//打印立体的信息
//希望编写一个程序：该程序可以打印正方形、长方形、圆形、三角形等各种不同
//图形的长度、面积信息
//目前只有上述三种图形，但是后续有可能需要扩展该功能
//Q1:上述的这些图形获取长度结果和面积结果的函数名称相同吗？？返回值相同吗？
//需要传递参数吗？？参数一样吗？？

//FiGure便是一个抽象类，无法创建出一个对象来
//如果后续希望创建出对象，那么必须继承Figure实现里面的全部纯虚函数
class Figure{
public:
    virtual double getPerimeter() = 0;
    virtual double getArea() = 0;
    virtual string getName() = 0;
};
//Q2:print需要接收一个参数，作为需要打印的图形，可以是正方形引用
//也可以是长方形引用、圆形引用、三角形引用
//需要写4个函数参数不同，但是代码逻辑基本一致的函数嘛？？？
#if 0
void print(XXX xxxx){
    cout << "当前图形" << xxxx << "它的面积是:" << xxx.getXXX()
        << ",周长是:" << xxx.getXXX() << endl;
}
#endif
void printFigure(Figure & figure){
    cout << "当前图形" << figure.getName() << "它的面积是:" << figure.getArea()
        << ",周长是:" << figure.getPerimeter() << endl;
}


class Rectangle : public Figure{
public:
    Rectangle(double length, double width)
    :_length(length)
    ,_width(width)
    {

    }
    //virtual在派生类对象中可以写，也可以不写
    //override也是可选的
    virtual double getPerimeter() override{
        return 2 * (_length + _width);
    }
    virtual double getArea() override{
        return _length * _width;
    }
    virtual string getName(){
        return "长方形";
    }
private:
    double _length;
    double _width;

};
const double PI = 3.14;
class Circle : public Figure {
public:
    Circle(double radius)
    :_radius(radius)
    {

    }
    virtual double getPerimeter(){
        return 2 * PI * _radius;
    }
    virtual double getArea(){
        return PI * _radius * _radius;
    }
    virtual string getName(){
        return "圆形";
    }
private:
    double _radius;
};

void test(){
    //Figure figure;
    //Figure * pf;
    //Rectangle rec;

    Rectangle rec(1, 2);
    Circle c(5);
    printFigure(rec);
    printFigure(c);
}

int main()
{
    test();
    return 0;
}

