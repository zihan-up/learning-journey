#include <iostream>
using std::cout;
using std::endl;
//复数：相加其实就是实部 + 实部，虚部 + 虚部
class Complex{
public:
    Complex(int real, int image)
    :_real(real)
    ,_image(image)
    {

    }

    void print(){
        cout << "_real=" << _real << ",_image=" << _image << endl;
    }
    //完全可以定义个成员函数来完成上述的功能
    //Complex add(Complex c2);

    friend Complex operator+(const Complex & c1, const Complex & c2);
private:
    //实部
    int _real;
    //虚部
    int _image;
};
//上一个案例中，将运算符写在了成员函数中，小问题就是+左右都是有操作数的
//但是如果写在成员函数中，其实只有一个参数，看起来不是对等的
//普通函数
//1.返回值是什么？
//2.函数的名称是什么？
//3.函数的形参是什么？普通函数非成员函数，没有this指针，+运算需要两个操作数
//需要将这个函数设置为Complex类的友元
Complex operator+(const Complex & c1, const Complex & c2){
    int real = c1._real + c2._real;
    int image = c1._image + c2._image;
    Complex temp(real, image);
    return temp;
}

void test(){
    Complex c1(1, 2), c2(3, 4);
    //下面的代码就是采用运算符重载实现的效果
    //但是默认情况下，编译器没有提供+运算符重载函数所以会出错
    //运算符重载和普通的成员函数其实没有什么本质性的区别，仅仅是看起来比较直观
    //所以使用成员函数也是可以完成相同的功能的
    //本质其实就是当我们写出下面的代码时，编译器会帮助我们去调用
    //c1.operator+(c2);成员函数
    Complex c3 = c1 + c2;
    c3.print();
}

class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {

    }
    friend Point operator+(const Point & p1, const Point & p2);

private:
    int _x;
    int _y;
};
//普通函数形式
//返回值、函数名称和使用成员函数还是普通函数没有太大的区别
//函数的形参会根据使用普通函数还是成员函数有变化，主要是因为存在this指针
Point operator+(const Point & p1, const Point & p2){
    int x = p1._x + p2._x;
    int y = p1._y + p2._y;
    Point temp(x, y);
    return temp;
}

void test2(){
    Point pt(1, 2), pt2(4, 8);
    Point pt3 = pt + pt2;

}
int main()
{
    test();
    return 0;
}

