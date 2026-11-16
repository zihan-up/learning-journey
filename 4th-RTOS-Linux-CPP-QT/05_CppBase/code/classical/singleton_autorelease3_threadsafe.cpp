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
        pthread_once(&_once, init);
        return _ps;
    }

    void print(){
        cout << "print::" << this << endl;
    }
private:
    //哪段代码需要多线程中保证只执行一次，那么就将代码放入init中
    static void init(){
        if(_ps == nullptr){
            atexit(destroy);
            _ps = new Singleton();
        }
    }
    
private:
    Singleton(){
        cout << "Singleton()" << endl;
    }
    //destroy函数还保留，但是该函数不是给外部应用程序去调用
    //的，而是注册给atexit的
    //在系统正常结束时，会调用destroy函数
    static void destroy(){
        cout << "destroy:" <<  _ps << endl;
        if(_ps){
            delete _ps;
            _ps = nullptr;
        }
    }
    ~Singleton(){
        cout << "~Singleton()" << endl;
    }
    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;
    static Singleton * _ps;
    static pthread_once_t _once;
};
Singleton * Singleton::_ps = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

void test(){
    Singleton::getInstance()->print();
}

int main()
{
    test();
    return 0;
}

