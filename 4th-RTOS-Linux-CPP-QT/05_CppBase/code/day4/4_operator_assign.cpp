#include <iostream>
using std::cout;
using std::endl;
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    Point(const Point & rhs)
    :_x(rhs._x)
    ,_y(rhs._y)
    {
        cout << "Point(const Point &)" << endl;
    }

    ~Point(){
        cout << "~Point()" << endl;
    }
    //尝试把编译器给我们提供的赋值运算符写出来
    //代码编写时是pt1 = pt2;
    //经过编译器处理过之后会变成什么样呢？？？
    //pt1.operator(pt2);
    //rhs其实就是pt2
    //赋值运算符函数的返回值Point &其实返回的应该是pt1
    Point & operator=(const Point & rhs){
        _x = rhs._x;
        _y = rhs._y;
        //返回值不知道该返回什么？？？
        return *this;
    }

    //下面这个函数是我们平时编写的成员函数
    //但是该成员函数经过编译器处理之后，会多出来一个隐形的参数
    //这个参数便是this指针
    void print(){
        //Point pt2(1, 2);
        //this = &pt2;
        cout << _x << "," << _y << endl;
    }
    //利用指针去修改所指向的值是可以的
    void modify(){
        this->_x = 3;
        this->_y = 5;
    }
#if 0
    //经过编译器处理解析过之后的print函数
    // Point * this;
    // Point * const this -------√
    // const Point * this
    void print(Point * const this){
        this = &pt2;
        cout << this->_x << "," << this->_y << endl;
    }
    后续我们调用pt.print()函数时，经过编译器处理过后的代码
    print(&pt);
#endif

private:
    int _x;
    int _y;
};
void test(){

    int a = 10, b = 20;
    a = b;

    Point pt1(1, 2), pt2(3, 4);
    pt1.print();
    pt2.print();
    //下面两行代码的效果完全一致只不过我们认为第一种方式更加简便
    pt1 = pt2;//赋值操作
    pt1.operator=(pt2);
    cout << "operator====" << endl;
    pt1.print();
    pt2.print();
    //Point pt3 = pt2;//拷贝操作

}



int main()
{
    test();
    return 0;
}

