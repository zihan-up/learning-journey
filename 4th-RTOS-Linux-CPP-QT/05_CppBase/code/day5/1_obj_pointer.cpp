#include <iostream>
using std::cout;
using std::endl;
//指向对象的指针
class Point{
public:
    Point(int x = 0, int y = 0)
    :_x(x)
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
    void print(){
        cout << _x << "," << _y << endl;
    }

private:
    int _x;
    int _y;
};

void test(){
    //这是一种初始化的方式，后续使用的时候再给它进行赋值即可
    Point * p = nullptr;
    Point pt(1, 2);
    //这是初始化的方式2
    Point * p2 = &pt;
    //初始化的方式3 指针去指向堆区
    Point * p3 = new Point(1, 3);
    //指针如何进行使用呢？？？？？？
    //箭头、解引用
    p2->print();
    p3->print();
    (*p2).print();
    (*p3).print();

    delete p3;
    p3 = nullptr;
}

//对象数组
void test2(){
    int arr[5];
    
    //如果这种方式进行声明，那么需要进行元素的实例化
    //需要借助于构造函数，只能够借助于无参构造函数来进行实例化
    //出错的原因是因为没有提供无参构造函数
    //Point pts[5];error 
    //如何解决上述问题呢？？？1.提供无参构造函数  2，使用下面的方式
    Point pts[5]{Point(1, 2), Point(1, 2), Point(1, 2), Point(1, 2), Point(1, 2)};

}

//堆对象
void test3(){
    int * pInt = new int(10);
    int * pInt2 = new int[10]();

    //Point
    Point * p1 = new Point(1, 2);
    //1.提供无参构造函数  2.使用{}来进行初始化
    Point * p2 = new Point[10]();

    p1->print();
    (*p1).print();

    (p2 + 1)->print();
    (*(p2 + 1)).print();
}

int main()
{
    test3();
    return 0;
}

