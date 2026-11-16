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
    //当没有主动编写拷贝构造函数的时候，可以完成拷贝的过程的
    //说明编译器有提供默认的拷贝构造函数的实现
    //尝试将编译器提供的拷贝构造函数写出来
    //其中rhs变量的名称相对比较固定，表示的是右操作数
    //还有对应的lhs表示的是左操作数
    //当使用一个已经存在的对象创建一个新对象
    //新老对象里面的值应当是相等的
    Point(const Point & rhs)
    :_x(rhs._x)
    ,_y(rhs._y)
    {
        cout << "Point(const Point &)" << endl;
    }


    //因为目前没有指针数据成员，也没有申请堆空间
    //此时析构函数的主要作用便是为了去打印一个日志，进行调试
    //查看销毁
    ~Point(){
        cout << "~Point()" << endl;
    }
    void print(){
        cout << "(" << _x << "," << _y << ")" <<  endl;
    }


private:
    int _x;
    int _y;
};


void test(){
    int x = 1;
    int y = x;
    cout << &x << ":" << &y << endl;
}
void test2(){
    Point pt1(1, 2);
    //pt1就是属于右操作数，pt2属于左操作数
    //当我们写出下面的代码时，编译器便会调用拷贝构造函数来完成pt2创建
    //下面这两种写法都表示的是拷贝构造函数
    Point pt2 = pt1;
    Point pt3(pt1);
    pt2.print();
}

int main()
{
    test2();
    return 0;
}

