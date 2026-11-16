#include <iostream>
using std::cout;
using std::endl;

template <class T1,class T2 = double,int kBase = 10>
T1 multiply(T2 t1, T2 t2){
	return t1 * t2 * kBase;
}
void test(){
    //1.2=====> T2类型 T2类型double
    //但是T1是什么呢？？？？推断不出来
    //cout << multiply(1.2,1.2) << endl;         //error
    //T1 = double
    cout << multiply<double>(1.2,1.2) << endl; //ok
}
template <class T1 = double,class T2 = double,int kBase = 10>
T1 multiply2(T2 t1, T2 t2){
	return t1 * t2 * kBase;
}
void test2(){
    //编译器可以推断出来T2=double
    //但是没法推断出T1
    //此时就使用了默认类型T1=double
    cout << multiply2(1.2,1.2) << endl; 
}

int main()
{
    test();
    return 0;
}

