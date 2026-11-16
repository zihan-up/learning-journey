#include <iostream>
using std::cout;
using std::endl;
//拷贝构造函数的调用时机
//1.使用一个已经存在的对象去创建一个新的对象
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
    void print(){
        cout << _x << "," << _y << endl;
    }

private:
    int _x;
    int _y;
};
//拷贝构造函数的调用场景1
void test(){
    Point pt(1, 2);
    Point pt2 = pt;
    Point pt3(pt);
}


//拷贝构造函数的调用场景2
//当对象作为函数的参数，形参和实参相结合的时候，那么会执行一次拷贝
//可以看到函数的形参pt和实参pt对象的地址值是不一样的
//但是构造函数只被调用了一次，所以另外形参的pt对象是通过拷贝构造函数
//创建的
//Point pt = pt1;其实就是调用场景1的变种
void func(Point pt){
    cout << &pt << endl;
    pt.print();
}
//如果希望避免这一次拷贝构造函数的调用，那么可以传递引用
//如果此时不希望去修改实参的值，可以怎么做呢？？？可以加上const
//void func2(const Point & pt);
void func2(Point & pt){
    cout << "func2::" << &pt << endl;
    pt.print();
}

void test2(){
    Point pt1(2, 3);
    cout << &pt1 << endl;
    //func(pt1);
    func2(pt1);
}


//拷贝构造函数的调用时机3
//函数的返回值是一个对象，执行return语句的时候
Point globalPoint(1, 2);
Point func3(){
    //默认是有拷贝构造函数的调用
    return globalPoint;
}
Point func4(){
    //执行func4函数的时候，构造函数会被调用两次
    //原因在于全局的对象依然会被创建
    //默认情况下没有拷贝构造函数的调用
    //实际上编译器有一个优化机制，可以加上去优化指令
    //-fno-elide-constructors --std=c++11
    Point localPoint(3, 4);
    return localPoint;
}

void test3(){
    func4();
}

//===============讨论的是返回引用，会减少这一次拷贝的过程
Point globalPoint2(1, 2);
Point & func5(){
    cout << "func5" << endl;
    //默认是有拷贝构造函数的调用
    return globalPoint;
}
//问题：func6可以返回引用吗？？？返回的是局部对象的引用
//局部对象出了作用域之后，那么便会被销毁
//Point & func6(){
Point func6(){
    Point localPoint(3, 4);
    return localPoint;
}

void test4(){
    //在这个地方依然会有拷贝构造函数的调用
    //刚好满足拷贝构造函数的调用时机1
    //用一个已经存在的对象去创建一个新的对象
    //Point pt = func5();
    Point & pt = func5();
}

int main()
{
    test4();
    return 0;
}

