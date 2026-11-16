#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
class Computer{
public:
    //给_brand指针数据成员进行初始化，让指针指向的是堆空间
    Computer(const char * brand, float price)
    :_brand(new char[strlen(brand) + 1]())
    ,_price(price)
    {
        //形参传递的字符串里面的值拷贝到堆空间这块区域
        strcpy(_brand, brand);
        cout << "Computer(" << _brand << ")" << endl;
    }

    //析构函数
    ~Computer(){
        cout << "~Computer(" << _brand << ")" << endl;

        if(_brand){
            //安全地回收
            delete [] _brand;
            _brand = nullptr;
        }
    }

    void print(){
        cout << "_brand=" << _brand << ",_price=" << _price << endl; 
    }


private:
    char * _brand;
    float _price;
};

//定义各种不同类型的对象，探究各种不同类型对象的析构函数的调用时机
//析构函数的调用时机等价于对象销毁的先后顺序这种说法
//全局对象
Computer globalObj("global", 1000);

void test(){
    //局部对象
    Computer localObj("localObj", 1200);
    //静态对象
    static Computer staticObj("staticObj", 1300);
    //堆对象
    Computer * pc = new Computer("heapObj", 1400);
    delete pc;
    pc = nullptr;
}

int main()
{
    test();
    cout << "end of test()" << endl;
    return 0;
}

