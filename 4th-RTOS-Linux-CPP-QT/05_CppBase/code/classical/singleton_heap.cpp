#include <iostream>
using std::cout;
using std::endl;
//单例模式的堆区写法
class Singleton{
public:
    //2.提供一个公有的静态方法，将创建好的对象暴露出去
    static Singleton * getInstance(){
        if(_ps == nullptr){
            _ps = new Singleton();
        }
        return _ps;
    }
    void print(){
        cout << "Singleton::print()" << endl;
    }
    //调用destroy函数即可，并且该函数可以反复被调用
    static void destroy(){
        if(_ps){
            delete _ps;
            _ps = nullptr;
        }
    }
    //3.拷贝构造函数删除
    Singleton(const Singleton & rhs) = delete;
private:
    //1.构造函数私有化
    Singleton(){}
    ~Singleton(){}
    static Singleton * _ps;
};
Singleton * Singleton::_ps = nullptr;

void test(){
    Singleton * p1 = Singleton::getInstance();
    Singleton * p2 = Singleton::getInstance();
    //Singleton s2 = *p1;
    p1->print();
    p2->print();

    //两次调用delete会导致double free的情况
    //这个可以直接不理会
    //也可以将析构函数设置为私有
    //delete p1;
    //delete p2;
    //此时并不是完全没有瑕疵，如果在使用过程中，提前调用了destroy
    //会导致后续的程序无法使用
    Singleton::destroy();
    Singleton::destroy();
}

int main()
{
    test();
    return 0;
}

