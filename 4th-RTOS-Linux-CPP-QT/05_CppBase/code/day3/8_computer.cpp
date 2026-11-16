#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//指针数据成员
class Computer{
public:
    //给_brand指针数据成员进行初始化，让指针指向的是堆空间
    Computer(const char * brand, float price)
    :_brand(new char[strlen(brand) + 1]())
    ,_price(price)
    {
        //形参传递的字符串里面的值拷贝到堆空间这块区域
        strcpy(_brand, brand);
        cout << "Computer(const char *, float)" << endl;
    }

    //析构函数
    ~Computer(){
        cout << "~Computer()" << endl;

        if(_brand){
            //安全地回收
            delete [] _brand;
            _brand = nullptr;
        }
    }

    void print(){
        cout << "_brand=" << _brand << ",_price=" << _price << endl; 
    }
    //发现其实有内存泄漏的问题，如何解决呢？
    //编写一个成员函数，在该函数中去调用delete操作
    //但是此时对于使用者来说，要求比较高
    //几不能够过早调用，也不能够不调用


private:
    char * _brand;
    float _price;
};
void test(){
    //const char * pstr = "hello";
    Computer c("Apple", 12000);
    //c.~Computer();
    c.print();
}

int main()
{
    test();
    return 0;
}

