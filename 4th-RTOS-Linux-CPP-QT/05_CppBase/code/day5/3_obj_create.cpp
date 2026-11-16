#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char * brand, float price)
    :_brand(new char[strlen(brand) + 1]())
    ,_price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(const char *, float)" << endl;
    }
private:
    ~Computer(){
        cout << "~Computer" << endl;
        if(_brand){
            delete [] _brand;
            _brand = nullptr;
        }
    }
public:
    void * operator new(size_t size){
        cout << "operator new::" << size << endl;
        void * result = malloc(size);
        return result;
    }
    void operator delete(void * p){
        free(p);
        cout << "operator delete" << endl;
    }

    void release(){
        delete this;
    }
    static void destroy(Computer * p){
        delete p;
    }


private:
    char * _brand;
    float _price;
};

void test(){

    Computer * pc = new Computer("Apple", 10000);

    //Computer c("Apple", 12000);

    //pc->release();
    //pc->release();可以解决，但是不可以反复调用

    Computer::destroy(pc);

    //delete pc;
}

int main()
{
    test();
    return 0;
}

