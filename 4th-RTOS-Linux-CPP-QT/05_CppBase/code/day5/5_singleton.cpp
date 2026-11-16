#include <iostream>
using std::cout;
using std::endl;
//单例对象创建在堆区
class Singleton{
public:
    //第一次调用时，没有创建所以需要创建一个对象
    //第二次调用，因为已经创建了一个对象，所以直接将该对象返回即可
    //需要设置一个指针，充当标记和指向对象的功能
    //标记刚开始的时候是nullptr，后续指向对象之后不再时nullptr
    static Singleton * getInstance(){
        if(_pInstance == nullptr){
            //还没有对象被创建
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
private:
    Singleton(){}
    Singleton(const Singleton & rhs) = delete;
    static Singleton * _pInstance;
};
Singleton * Singleton::_pInstance = nullptr;
void test(){
    Singleton * ps1 = Singleton::getInstance();
    Singleton * ps2 = Singleton::getInstance();
    cout << ps1 << endl;
    cout << ps2 << endl;

    delete ps1;
    //delete ps2;
}

int main()
{
    test();
    return 0;
}

