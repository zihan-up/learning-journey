#include <iostream>
//using编译指令
//这条指令代表的含义是将std命名空间中的全部实体全部
//引入到当前代码中
//无论是刚刚的cout、endl、其他各种各样的其他实体
//全部都会引入进来
//本来我们只是希望引入cout、endl，但是由于对于std
//命名空间里面的其他实体不熟悉，那么很容易引发冲突
using namespace std;

void string(){
    cout << "string" << endl;
}

void test(){
    cout << "hello,world" << endl;
    string s1;
}

int main()
{
    test();
    return 0;
}

