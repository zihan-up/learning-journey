#include <iostream>
using std::cout;
using std::endl;
//思考：如何保证某个类只能创建一个对象呢？
//1.一定得保证构造函数不能被外部程序随意的调用
//2.接下来应该怎么办呢？此时外部程序一个对象都得不到？？？
//内部创建一个对象出来，暴露给外部程序
//3.设计一个函数，该函数可以是普通的成员函数嘛？？？
//需要是静态成员函数
//4.返回的对象需要是引用，但是又不能是局部对象的引用
//如果不返回引用，那么又会进行拷贝操作,需要将对象放置在静态区，返回引用
//5.需要将拷贝构造函数删除
class Singleton{
private:
    Singleton(){}
public:
    static Singleton & getInstance(){
        static Singleton s;
        cout << &s << endl;
        return s;
    }
    Singleton(const Singleton & rhs) = delete;
};
void test(){
    Singleton::getInstance();
    Singleton::getInstance();
}

int main()
{
    test();
    return 0;
}

