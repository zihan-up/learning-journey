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

    //成员函数会不会对类对象的大小产生影响呢？？
    //成员函数位于程序代码区，此时的对象位于栈区
    //调用print显示的结果肯定都是正确的
    //它们是如何正确的关联在一起的呢？？？
    void print(){
        cout << _x << "," << _y << endl;
    }


//private:
    int _x;
    int _y;
};
void test(){
    Point pt(1, 2);
    Point pt2(2, 4);
    pt.print();
    pt2.print();
    cout << sizeof(Point) << endl;
    cout << sizeof(pt) << endl;
}

class Test{
private:
    int _x;  //4
    double _y; // 8
};

class Test2{
private:
    double _y;
    int _x;
};

void test2(){
    cout << sizeof(Test) << endl;
    cout << sizeof(Test2) << endl;
}


class x{
    char a;
    int b;
    short c;
    char d;
}AA;  //12

class y{
    int b;
    char a;
    char d;
    short c;
}BB;
void test3(){
    cout << "sizeof(x)=" << sizeof(AA) << endl;
    cout << "sizeof(y)=" << sizeof(BB) << endl;
}


class AA{
    int a;
    char b;
    short c;
    int d;
    class FF{
        int a1;
        char b1;
        short c1;
        char d1;
    }SFF;

    char e;

}SAA; // 28

class BB{
    int a;
    char b;
    short c;
    int d;
    class FF{
        double a1;//因为出现了double 8字节类型的变量，所以最终对齐需要对齐到8字节
        char b1;
        short c1;
        char d1;
    }SFF;

    char e;
}SBB; //40

class CC{
    char e[2];
    short h;

    //class A需要对齐到8字节边界，起始必须也从8字节整数倍开始
    class A{
        int a;
        //最大成员整数倍开始存储
        //结构体本身也需要对齐，也就是最终需要存储double 8的整数倍
        double b;
        float c;
    }SAA;

}SCC;

void test4(){
    cout << sizeof(SAA) << endl;
    cout << sizeof(SBB) << endl;
    cout << sizeof(SCC) << endl;
}

int main()
{
    test4();
    return 0;
}

