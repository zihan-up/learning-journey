#include <iostream>
using std::cout;
using std::endl;
//单例:
//存放在静态区和存放在堆区两种方式
//1.构造函数私有化
//2.需要在类的内部创建出一个对象，并且只能够创建出一个对象（
//静态区：static Singleton s;
//堆区：需要判断，加以控制）
//3.创建好的对象暴露出去
//4.回收的时候，析构函数私有化；拷贝构造函数、赋值运算符函数删除
class Singleton{
public:
    static Singleton * getInstance(){
        if(_ps == nullptr){
            _ps = new Singleton();
        }
        return _ps;
    }
    //这个地方不太健壮
    static void destroy(){
        cout << "destroy:" <<  _ps << endl;
        if(_ps){
            delete _ps;
            _ps = nullptr;
        }
    }
    void print(){
        cout << "print::" << this << endl;
        cout << "Singleton::print:" << _a << endl;
    }
    
private:
    Singleton(){
        cout << "Singleton()" << endl;
    }
    ~Singleton(){
        cout << "~Singleton()" << endl;
    }
    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;
    static Singleton * _ps;
    int _a = 10;
};
Singleton * Singleton::_ps = nullptr;


void test(){
    Singleton::getInstance()->print();
    Singleton::destroy();
    Singleton::getInstance()->print();

    Singleton::destroy();
}

int main()
{
    test();
    return 0;
}

