#include <iostream>
using std::cout;
using std::endl;

class Test{
public:
    Test()
    :_a(10)
    ,_b(20)
    ,_p1(new int(10))
    ,_p2(new int(20))
    {

    }
    ~Test(){
        if(_p1){
            delete _p1;
            _p1 = nullptr;
        }
        if(_p2){
            delete _p2;
            _p2 = nullptr;
        }
    }

    //普通的成员函数
    //this指针：Type * const this
    void func(){
        _a = 20;
        _b = 30;
        _p1 = new int(20);
        *_p1 = 50;
        _p2 = new int(50);
        *_p2 = 60;
    }
    //const成员函数
    //this指针：const Type * const this 
    void func() const{
        _a = 20;
        _b = 30;
        _p1 = new int(20);
        *_p1 = 50;
    }


private:
    int _a;
    const int _b;
    int * _p1;
    const int * _p2;
};



void test(){

}

int main()
{
    test();
    return 0;
}

