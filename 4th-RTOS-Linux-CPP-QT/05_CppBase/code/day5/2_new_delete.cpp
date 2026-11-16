#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//指向对象的指针
class Point{
public:
    Point(int x = 0, int y = 0)
    :_x(x)
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    ~Point(){
        cout << "~Point()" << endl;
    }
    void print(){
        cout << _x << "," << _y << endl;
    }
    //说明编译器默认有提供operator new库函数
    //本质便是进一步调用malloc库函数
    //size其实便和对象所占空间大小知识点关联在了一起
    void * operator new(size_t size){
        cout << "operator new" << size << endl;
        void * result = malloc(size);
        return result;
    }

    void operator delete(void * p){
        cout << "operator delete" << endl;
        free(p);
    }


private:
    int _x;
    int _y;
};

class Computer{
public:
    Computer(const char * brand, float price)
    :_brand(new char[strlen(brand) + 1]())
    ,_price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(const char *, float)" << endl;
    }

    ~Computer(){
        cout << "~Computer" << endl;
        if(_brand){
            delete [] _brand;
            _brand = nullptr;
        }
    }

    void * operator new(size_t size){
        cout << "operator new::" << size << endl;
        void * result = malloc(size);
        return result;
    }

    void operator delete(void * p){
        free(p);
        cout << "operator delete" << endl;
    }

private:
    char * _brand;
    float _price;
};

void test(){
    //Point * p = new Point(1, 2);

    Computer * pc = new Computer("Apple", 10000);



    //delete p;

    delete pc;
}

int main()
{
    test();
    return 0;
}

