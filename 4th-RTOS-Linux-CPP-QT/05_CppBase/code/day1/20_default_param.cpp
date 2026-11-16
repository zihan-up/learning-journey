#include <iostream>
using std::cout;
using std::endl;
//默认参数
//
//
//
//这两个参数必须要提供，如果不提供，那么便会出错
//有没有其他的处理思路呢？？？？
//如果不提供，那么就使用系统提供的默认值
//这个就是默认参数，或者说缺省参数
void query(int pagesize = 20, int currentPage = 0){
    cout << pagesize << currentPage << endl;
}



void test(){
    //提供的值优先级高于默认值的优先级
    query(40, 1);
    //因为没有提供值，所以全部使用默认值
    query();
    //10给谁呢？参数匹配是从左往右的，10给第一个形参
    //第二个形参使用默认值
    query(10);
}

int main()
{
    test();
    return 0;
}

