#include <iostream>
using std::cout;
using std::endl;
//嵌套类  + 静态对象
class Singleton{
public:
    static Singleton * getInstance(){
        //下面的代码在多线程场景下是不安全的
        //多线程的情况下，多个线程竞争访问init函数
        //但是只会有唯一的一个函数能够顺利执行init
        pthread_once(&_once, init);
        return _ps;
    }

    //这个地方不太健壮
#if 0
    static void destroy(){
        cout << "destroy:" <<  _ps << endl;
        if(_ps){
            delete _ps;
            _ps = nullptr;
        }
    }
#endif
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

    //init函数在多线程的情况下，只会被执行一次
    //init需要放置在private区域
    static void init(){
        if(_ps == nullptr){
            _ps = new Singleton();
        }
    }
    //在外部类的私有区域，创建一个内部类
    class AutoRelease{
    public:
        AutoRelease(){
            cout << "AutoRelease()" << endl;
        }
        ~AutoRelease(){
            cout << "~AutoRelease()" << endl;
            //外部类的静态数据成员
            if(_ps){
                delete _ps;
                _ps = nullptr;
            }
        }
    };

    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;
    static Singleton * _ps;
    //如果把static去了，那么该对象的初始化没有问题
    //但是该对象的销毁会在Singleton单例对象销毁的时候销毁
    static AutoRelease _ar;//持有一个静态的内部类对象
    
    static pthread_once_t _once;

};
Singleton * Singleton::_ps = nullptr;
//Singleton::AutoRelease是类型
//Singleton::_ar是变量
Singleton::AutoRelease Singleton::_ar;
//PTHREAD_ONCE_INIT是一个宏定义
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

void test(){
    Singleton::getInstance()->print();
}

int main()
{
    test();
    return 0;
}

