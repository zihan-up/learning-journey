#include <iostream>
using std::cout;
using std::endl;
//不仅非类型参数可以设置默认值，类型参数也可以设置默认值
//设定的规则完全和之前介绍的默认参数是一样的
template <class T = int,int kBase = 10>
T multiply(T x, T y){
return x * y * kBase;
}
//关于类型参数：有三种情形
//1.用户显式实例化时指定的类型
//2.编译器自动推断出来的类型
//3.推断不出来时，使用的默认类型
void test0(){
	double d1 = 1.2, d2 = 1.2;
	cout << multiply<int>(d1,d2) << endl;    //ok 10
	//对于下面这个案例，便是编译器自动推断出来的类型double
    //通过这个案例：
    //用户指定的类型 > 推断出来的类型  > 默认类型
    cout << multiply(d1,d2) << endl;        //ok 14.4
}

void test(){

}

int main()
{
    test0();
    return 0;
}

