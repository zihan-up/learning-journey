#include <iostream>
using std::cout;
using std::endl;
//讨论：外部类和内部类之间访问权限上面的关系
class Outer{
public:


private:
    class Inner{
    public:
        void inner_func(Outer outer){
            //内部类可以直接访问外部类的静态数据成员
            cout << _out_a << endl;
            //内部类可以通过类名作用域限定符的方式访问外部类的静态
            //数据成员
            cout << Outer::_out_a << endl;
            //内部类可以通过对象访问私有数据成员
            cout << outer._out_b << endl;
        }
        //friend class Outer;

    private:
        int _a;
        static int _b;
    };
public:
    void outer_func(Inner inner){
        //外部类不可以直接去访问内部类的私有的静态数据成员
        //外部类也不可以通过类名作用域限定的方式去访问
        //内部类的私有数据成员
        //通过对象去访问内部类的私有数据成员也是不可以的
        //以上三种情况，如果想要能够正常执行，那么需要设置为友元
        cout << _a << endl;//error
        cout << Inner::_b << endl;
        cout << inner._a << endl;
    }
private:
    static int _out_a;
    int _out_b;
    //外部类中可以创建出内部类对象
    Inner inner;
};
int Outer::_out_a = 0;

void test(){
    //外部应用程序无创建
    Inner inner;
    Outer::Inner inner2;
}

int main()
{
    test();
    return 0;
}

