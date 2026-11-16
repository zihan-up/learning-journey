#include <iostream>
using std::cout;
using std::endl;
//构造函数
class Point{
public:
#if 0
    Point(int x, int y){
        //C++认为下面这两行严格意义上来说，依然不能够算作初始化
        //而是应该叫做赋值操作
        _x = x;
        _y = y;
        cout << "Point()" << endl;
    }
#endif
    Point(int x, int y)
    :_x(x)//()里面表示需要初始化的值
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
    //还可以再写一个无参构造函数
    //构造函数可以形成函数重载
    Point(){

    }


//private:
    int _x;
    int _y;
};
void test(){
    //创建类对象的过程会调用构造函数
    //但是下面的这个写法会调用无参构造函数
    //因为此时自己提供了一个有参构造函数，默认的无参构造函数
    //编译器不会再提供，所以出错
    //Point pt;error
    Point pt(1, 2);
    //Point pt;
    cout << pt._x << "," << pt._y << endl;
}

int main()
{
    test();
    return 0;
}

