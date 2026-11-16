#include <iostream>
#include <set>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::pair;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

void test()
{
    //set的基本特征
    //1、存放的是key类型，key值是唯一的，不能重复
    //2、默认会按照key进行升序排列
    //3、底层实现是红黑树
    set<int> number = {1, 3, 6, 9, 8, 3, 2, 5, 1, 8};
    /* set<int, std::greater<int>> number = {1, 3, 6, 9, 8, 3, 2, 5, 1, 8}; */
    display(number);

    cout << endl << "set的查找" << endl;
    size_t cnt = number.count(6);
    cout << "cnt = " << cnt << endl;

    set<int>::iterator it = number.find(7);
    if(it == number.end())
    {
        cout << "该元素不存在set中" << endl;
    }
    else
    {
        cout << "该元素存在set中 " << *it << endl;
    }

    cout << endl << "set的insert操作" << endl;
    pair<set<int>::iterator, bool> ret = number.insert(4);
    /* auto ret = number.insert(4); */
    if(ret.second)
    {
        cout << "插入成功 " << *ret.first << endl;
    }
    else
    {
        cout << "插入失败，该元素存在set中" << endl;
    }
    display(number);

    cout << endl << endl;
    vector<int> vec = {1, 7, 11, 33, 22, 6};
    number.insert(vec.begin(), vec.end());
    display(number);

    cout << endl << endl;
    number.insert({10, 40, 20, 70});
    display(number);

    cout <<endl << "set的erase操作" << endl;
    number.erase(4);
    number.erase(10);
    display(number);

    cout << endl << endl;
    it = number.begin();
    cout << "*it = " << *it << endl;
    /* *it = 100;//error */
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

