#include <iostream>
#include <deque>

using std::cout;
using std::endl;
using std::deque;

void test0()
{
    deque<int> deq = {1, 5, 3, 2, 2, 2, 2, 5, 2, 2, 2, 4};
    for(auto it = deq.begin(); it != deq.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //需求：删除所有的2
    //现象：不能删除连续重复的元素
    for(auto it = deq.begin(); it != deq.end(); ++it)
    {
        if(2 == *it)
        {
            deq.erase(it);
        }
    }

    cout << endl << "删除掉了所有2之后的结果" << endl;
    for(auto it = deq.begin(); it != deq.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

void test()
{
    deque<int> deq = {1, 5, 3, 2, 2, 2, 2, 5, 2, 2, 2, 4};
    for(auto it = deq.begin(); it != deq.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    //需求：删除所有的2
    //现象：不能删除连续重复的元素
    for(auto it = deq.begin(); it != deq.end(); )
    {
        if(2 == *it)
        {
            deq.erase(it);
        }
        else
        {
            ++it;
        }
    }

    cout << endl << "删除掉了所有2之后的结果" << endl;
    for(auto it = deq.begin(); it != deq.end(); ++it)
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

