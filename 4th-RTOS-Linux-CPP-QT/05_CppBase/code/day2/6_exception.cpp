#include <iostream>
using std::cout;
using std::endl;

double division(double x,double y){
    if(y == 0){
        throw "Deivision by zero";
    }
    if(x == 0){
        throw 4.8;
    }
    return x/y;
}

void test0(){
    try{
        //try里面的代码如果抛出了异常，那么后续的代码便不会继续执行
        //cout << division(9,0) << endl;
        //cout << division(0,100) << endl;
        cout << division(1000,100) << endl;
        cout << "try over" << endl;
    }catch(const char * msg){ //catch的小括号里是类型
        cout << "hello," << msg << endl;
    }catch(double x){
        cout << x << endl;
        cout << "please change a num!" << endl;
    }
    cout << "over" << endl;
}


void test(){

}

int main()
{
    test0();
    return 0;
}

