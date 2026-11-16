#include <iostream>
using std::cout;
using std::endl;
//函数模板的重载
//模板1
template <class T>
T add(T t1, T t2){
    cout << "template1" << endl;
    return t1 + t2;
}
//模板2
template <class T1, class T2>
T1 add(T1 t1, T2 t2){
    cout << "template2" << endl;
    return t1 + t2;
}
void test(){
    double a = 10;
    int b = 20;
    cout << add(a, b) << endl;
    cout << add(b, a) << endl;

    cout << "================" << endl;
    cout << add<int,int>(a, b) << endl;//模板2
    //模板1：T=int,a转int
    //模板2：T1=int,a转int T2=int
    cout << add<int>(a, b) << endl;//模板1
    //模板1：T=int,b本身是int，将a转为int
    //模板2：T1=int,T2=double不需要进行强转
    cout << add<int>(b, a) << endl;//模板2
}

int main()
{
    test();
    return 0;
}

