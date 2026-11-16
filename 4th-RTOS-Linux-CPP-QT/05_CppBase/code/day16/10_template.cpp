#include <iostream>
using std::cout;
using std::endl;
//类型参数、非类型参数
//非类型参数kBase永远无法自动推断出来
template <class T,int kBase>
T multiply(T x, T y){
	return x * y * kBase;
}
void test0(){
    int i1 = 3,i2 = 4;
    //此时想要进行隐式实例化就不允许了，因为kBase无法推导
    //cout << multiply(i1,i2) << endl;  //error
    cout << multiply<int,10>(i1,i2) << endl;   //ok
}
template <class T,int kBase = 10>
T multiply2(T x, T y){
	return x * y * kBase;
}
void test(){
    int i1 = 3,i2 = 4;
    //此时非类型参数设定了一个默认值10
    //当没有提供的时候，那么便会使用默认值10
    cout << multiply2(i1,i2) << endl;

}

int main()
{
    test();
    return 0;
}

