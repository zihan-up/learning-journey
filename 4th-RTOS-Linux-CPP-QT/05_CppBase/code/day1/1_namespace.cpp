#include <iostream>
using std::cout;
using std::endl;

int age = 10;

namespace wd{
//定义了实体
    int age = 20;
    int value = 10;
}// end of namespace wd 
namespace wh{
    int age = 30;
} // end of namespace wh


void test(){
    //有何种优缺点？？？？？
    //优点：冲突产生的概率非常非常小
    //缺点：编写起来非常麻烦，
    //如果代码中频繁使用，那么会非常繁琐
    cout << wd::age << endl;
    cout << wh::age << endl;
}

void test2(){
    //std::cout << xxx << endl;
}

int main()
{
    test();
    return 0;
}

