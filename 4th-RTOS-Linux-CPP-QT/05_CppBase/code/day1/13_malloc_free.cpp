#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//C语言操作堆空间
void test(){
    //申请4字节的空间
    //1.调用malloc库函数去申请堆空间
    //.此时申请出来的堆空间是未初始化的
    int * pInt = (int *)malloc(sizeof(int));
    //2.严谨起见，一般需要进行初始化的操作
    memset(pInt, 0, sizeof(int));
    *pInt = 20;
    cout << *pInt << endl;
    cout << pInt << endl;
    //3.回收堆空间
    free(pInt);
}

//申请数组空间 4 * 5 空间
void test2(){
    //1.申请未初始化的堆空间
    int * pInt = (int *)malloc(sizeof(int) * 5);
    //2.初始化操作
    memset(pInt, 0, sizeof(int) * 5);
    //使用
    for(int i = 0; i < 5; ++i){
        pInt[i] = (i + 1) * 10;
    }
    for(int i = 0; i < 5; ++i){
        cout << pInt[i] << endl;
    }
    free(pInt);
}

//下面是使用c++里面的new/delete表达式来进行操作
//申请4字节的空间
void test3(){
    int * pInt = new int();
    //使用new也不需要进行初始化操作
    *pInt = 20;
    cout << *pInt << endl;
    delete pInt;
}
//申请 4 * 5
void test4(){
    int * pInt = new int[5]();
    for(int i = 0; i < 5; ++i){
        pInt[i] = i;
    }
    //这是需要特别注意的地方，需要添加一个[]，否则无法回收全部的空间
    delete [] pInt;
    pInt = nullptr;
}

void test5(){
    //默认初始化的是0值
    int * pInt = new int();
    cout << *pInt << endl;
    delete pInt;
    pInt = nullptr;
    //初始化的是10
    int * pInt2 = new int(10);
    cout << *pInt2 << endl;
    delete pInt2;
    pInt2 = nullptr;
}

int main()
{
    test5();
    return 0;
}

