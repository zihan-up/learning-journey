#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void test0()
{
    vector<int> vec = {1, 5, 3, 2, 2, 2, 2, 5, 2, 2, 2, 4};
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //需求：删除所有的2
    //现象：不能删除连续重复的元素
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        if(2 == *it)
        {
            it = vec.erase(it);
        }
    }

    cout << endl << "删除掉了所有2之后的结果" << endl;
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

void test()
{
    vector<int> vec = {1, 5, 3, 2, 2, 2, 2, 5, 2, 2, 2, 4};
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //需求：删除所有的2
    //现象：不能删除连续重复的元素
    for(auto it = vec.begin(); it != vec.end(); )
    {
        if(2 == *it)
        {
            it = vec.erase(it);
        }
        else
        {
            ++it;
        }
    }

    cout << endl << "删除掉了所有2之后的结果" << endl;
    for(auto it = vec.begin(); it != vec.end(); ++it)
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

