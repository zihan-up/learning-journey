#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

void test0()
{
    list<int> number = {1, 5, 3, 2, 2, 2, 2, 5, 2, 2, 2, 4};
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //需求：删除所有的2
    //现象：不能删除连续重复的元素
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        if(2 == *it)
        {
            //第一种方式
            /* auto tmp = it++; */
            /* number.erase(tmp); */
            //第二种方式
            /* number.erase(it++); */
            //第三种方式
            it = number.erase(it);
        }
    }

    cout << endl << "删除掉了所有2之后的结果" << endl;
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

void test()
{
    list<int> number = {1, 5, 3, 2, 2, 2, 2, 5, 2, 2, 2, 4};
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //需求：删除所有的2
    //现象：不能删除连续重复的元素
    for(auto it = number.begin(); it != number.end(); )
    {
        if(2 == *it)
        {
            it = number.erase(it);
        }
        else
        {
            ++it;
        }
    }

    cout << endl << "删除掉了所有2之后的结果" << endl;
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;
}
int main(int argc, char *argv[])
{
    test();
    return 0;
}

