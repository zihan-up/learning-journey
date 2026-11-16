#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::set;

void test0()
{
    set<int> number = {1, 3, 4, 9, 7, 11, 13, 14, 1, 3, 7};
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //删除奇数
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        if(1 == *it % 2)
        {
            it = number.erase(it);
        }
    }

    cout <<endl << "删除所有的奇数之后的结果" << endl;
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

}

void test()
{
    set<int> number = {1, 3, 4, 9, 7, 11, 13, 14, 1, 3, 7};
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //删除奇数
    for(auto it = number.begin(); it != number.end(); )
    {
        if(1 == *it % 2)
        {
            it = number.erase(it);
        }
        else
        {
            ++it;
        }
    }

    cout <<endl << "删除所有的奇数之后的结果" << endl;
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

