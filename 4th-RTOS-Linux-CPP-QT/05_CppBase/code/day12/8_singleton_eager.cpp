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
        //atexit(destroy);
        //对于饿汉模式来说，atexit自动销毁的方式不是特别友好
        return _ps;
    }
    static void destroy(){
        cout << "destroy:" <<  _ps << endl;
        if(_ps){
            delete _ps;
            _ps = nullptr;
        }
    }
    void print(){
        cout << "print::" << this << endl;
    }
    
private:
    Singleton(){
        cout << "Singleton()" << endl;
    }
    ~Singleton(){
        cout << "~Singleton()" << endl;
    }
    friend class AutoRelease;
    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;
    static Singleton * _ps;
};
//静态指针数据成员直接初始化为指向堆空间
Singleton * Singleton::_ps = new Singleton();

class AutoRelease{
public:
    AutoRelease(Singleton * ps)
    :_ps(ps)
    {
        cout << "AutoRelease(Singleton *)" << endl;
    }
    ~AutoRelease(){
        cout << "~AutoRelease" << endl;
        if(_ps){
            //需要访问私有的析构函数，所以当前类需要
            //设置为Singleton的友元类
            delete _ps;
            _ps = nullptr;
            Singleton::_ps = nullptr;
        }
    }
    //对箭头访问运算符进行重载


private:
    Singleton * _ps;
};

void test(){
    AutoRelease ar(Singleton::getInstance());
}

int main()
{
    test();
    return 0;
}

