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

    //对于+=运算符进行重载
    Complex & operator+=(const Complex & c2){
        _real += c2._real;
        _image += c2._image;
        return *this;
    }

private:
    //实部
    int _real;
    //虚部
    int _image;
};
// int a = 10, b = 4;
// a += b;
//

void test(){
    Complex c1(1, 2), c2(3, 4);
    //编译器会将下面的代码解析成c1.operator+=(c2);
    c1 += c2;
    c1.print();
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

