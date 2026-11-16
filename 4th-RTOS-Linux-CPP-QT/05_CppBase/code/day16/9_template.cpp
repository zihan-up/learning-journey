#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//特化模板：需要有通用模板先存在，才能够有特化模板
template <class T>
T add(T t1, T t2){
    return t1 + t2;
}
//普通模板处理不了的情况，两种解决方案
//1.编写一个普通的函数（最为推荐的方式）
//2，编写一个特化模板（简单了解即可，后续看到认识即可）
template <>
const char * add<const char *>(const char * p1, const char * p2){
    char * temp = new char[strlen(p1) + strlen(p2) + 1]();
    strcpy(temp, p1);
    strcat(temp, p2);
    return temp;
}
void test(){
    const char * pstr1 = "hello";
    const char * pstr2 = "world";
    const char * pstr3 = add(pstr1, pstr2);
    cout << pstr3 << endl;
    delete [] pstr3;
}

int main()
{
    test();
    return 0;
}

