#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

void test()
{
    vector<int> vec = {1, 3, 6, 9, 5, 7, 3};
    /* priority_queue<int> pque(vec.begin(), vec.end()); */
    //优先级队列底层使用的是堆排序（默认是大根堆）
    //步骤：当有新的元素插入的时候，会将堆顶与新插入的元素进行比较，如果堆顶比新
    //插入的元素要小，也就是满足std::less,那么新插入的元素会作为新的堆顶;当堆顶
    //比新插入的元素要大的，那么就不满足std::less,那么老的堆顶依旧还是堆顶
    priority_queue<int> pque;

    for(size_t idx = 0; idx != vec.size(); ++idx)
    {
        pque.push(vec[idx]);
        cout << "优先级最高的元素:" << pque.top() << endl;
    }
    cout << endl;

    while(!pque.empty())
    {
        cout << pque.top() << "  ";
        pque.pop();
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

