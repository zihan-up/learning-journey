#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <iterator>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::set;
using std::ostream_iterator;
using std::back_inserter;
using std::back_insert_iterator;
using std::front_inserter;
using std::front_insert_iterator;
using std::inserter;
using std::insert_iterator;
using std::copy;

void test()
{
    vector<int> vec = {1, 3, 9, 7, 4};
    list<int> lst = {11, 44, 88, 33, 22};
    //将list中的所有元素插入到vector的尾部
    copy(lst.begin(), lst.end(), back_inserter(vec));//插入动作
    //遍历vector
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, "  "));//遍历
    cout << endl;

    cout << endl << endl;
    //将vector中的所有元素插入到list的头部
    copy(vec.begin(), vec.end(), front_inserter(lst));
    copy(lst.begin(), lst.end(), ostream_iterator<int>(cout, "  "));//遍历
    cout << endl;

    cout << endl << endl;
    set<int> setNum = {1, 12, 45, 78, 44, 33, 22};
    auto it = setNum.begin();
    //将vector中的所有元素插入到set中
    copy(vec.begin(), vec.end(), inserter(setNum, it));
    copy(setNum.begin(), setNum.end(), ostream_iterator<int>(cout, "  "));//遍历
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


