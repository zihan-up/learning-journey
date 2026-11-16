#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void test()
{
    /* vector<int> number;//1、创建无参的对象 */
    /* vector<int> number(10);//2、count个相同的元素 */
    /* //3、迭代器范围 */
    /* int arr[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10}; */
    /* vector<int> number(arr, arr + 10);//左闭右开[,) */
    //4、拷贝构造或者移动构造
    //5、使用大括号的方式
    vector<int> number = {1, 3, 5, 7, 9, 8, 6, 4, 2, 10};

    //遍历
    //使用下标进行遍历
    for(size_t idx = 0; idx != number.size(); ++idx)
    {
        cout << number[idx] << "  ";
    }
    cout << endl;

    vector<int>::iterator it;//使用未初始化的迭代器
    for(it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    /* vector<int>::iterator it2 = number.begin();//使用已初始化的迭代器 */
    auto it2 = number.begin();//使用已初始化的迭代器
    for(; it2 != number.end(); ++it2)
    {
        cout << *it2 << "  ";
    }
    cout << endl;

    //增强for循环
    for(auto &elem : number)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

class Base
{
public:
    typedef int A;
};

int main(int argc, char *argv[])
{
    Base::A a;
    test();
    return 0;
}

