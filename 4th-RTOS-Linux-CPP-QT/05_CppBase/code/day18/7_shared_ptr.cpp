#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::vector;
using std::shared_ptr;
using std::endl;

void test(){
    shared_ptr<int> sp(new int(10));
    cout << *sp << endl;
    cout << sp.get() << endl;
    cout << sp.use_count() << endl;
    //随后执行一次拷贝
    shared_ptr<int> sp2 = sp;
    cout << sp.use_count() << endl;
    cout << sp2.use_count() << endl;
    cout << *sp << ":" << *sp2 << endl;
    //再进行一次赋值操作
    shared_ptr<int> sp3(new int(20));
    cout << sp3.use_count() << endl;
    sp3 = sp;
    cout << sp.use_count() << endl;
    cout << sp2.use_count() << endl;
    cout << sp3.use_count() << endl;
    cout << *sp3 << endl;
}
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {}
    void print(){
        cout << _x << "," << _y << endl;
    }
private:
    int _x;
    int _y;
};

void test2(){
    shared_ptr<Point> sp(new Point(1, 0));
    cout << sp.use_count() << endl;//1
    shared_ptr<Point> sp2(std::move(sp));
    cout << sp.use_count() << endl;//0
    cout << sp2.use_count() << endl;//1
    cout << sp.get() << endl;
    sp->print();//error丧失了对于堆空间的控制权
}


//作为容器的元素
void test3(){
    vector<shared_ptr<Point>> vec;
    //会向vector里面存入数据，会调用拷贝构造函数
    shared_ptr<Point> sp(new Point(0, 0));
    cout << sp.use_count() << endl;//1
    vec.push_back(sp);
    cout << sp.use_count() << endl;//2
}

int main()
{
    test3();
    return 0;
}

