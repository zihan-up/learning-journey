#include <iostream>
using std::cout;
using std::endl;
//上述的方式其实就是using声明机制
//因为不需要std命名空间里面的其他实体，不引入这些实体
//如果当前代码中定义了一个string函数，也不会产生冲突
void string(){
    cout << "string" << endl;
}
void test(){
    string();
}

int main()
{
    test();
    return 0;
}

