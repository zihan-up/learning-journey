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

    //对于+运算符进行重载
    //1.返回值应该是什么？Complex但是不要返回引用
    //2.函数名称应该是什么?函数的名称不能够像自定义的成员函数一样那么随意
    //3.函数的形参是什么？可以加const、可以加引用
    Complex operator+(const Complex & c2){
        //至于这里面怎么写，没有标准的统一的答案，根据具体的业务来确定
        int real = _real + c2._real;
        int image = _image + c2._image;
        Complex temp(real, image);
        return temp;
    }

    // 1 + 2i
    // 1 - 2i
    void print(){
        cout << "_real=" << _real << ",_image=" << _image << endl;
    }
    //完全可以定义个成员函数来完成上述的功能
    //Complex add(Complex c2);

private:
    //实部
    int _real;
    //虚部
    int _image;
};


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


//再来看一个案例：求解点的坐标相加操作
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {

    }

    //1.返回值是什么？Point
    //2.函数的名称是什么？相对来说，最为固定的一个写法
    //3.函数的形参是什么？因为有一个隐形的this指针，所以只需要提供一个参数即可
    Point operator+(const Point & p2){
        int x = _x + p2._x;
        int y = _y + p2._y;
        Point pt(x, y);
        return pt;
    }

private:
    int _x;
    int _y;
};
void test2(){
    Point pt1(1, 2), pt2(3, 5);
    //可以进行坐标点的相加操作
    //这里面最重要的是会调用operator+函数，如果参数能够对应上，那么便可以正常运行
    Point pt3 = pt1 + pt2;
}

int main()
{
    test();
    return 0;
}

