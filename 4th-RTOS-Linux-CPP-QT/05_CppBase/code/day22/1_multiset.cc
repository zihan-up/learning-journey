#include <iostream>
#include <set>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::multiset;
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
    //multiset的基本特征
    //1、存放的是key类型，key值是不唯一的，可以重复
    //2、默认会按照key进行升序排列
    //3、底层实现是红黑树
    multiset<int> number = {1, 3, 6, 9, 8, 3, 2, 5, 1, 8, 8, 8};
    display(number);

    cout << endl << "multiset的查找" << endl;
    size_t cnt = number.count(6);
    cout << "cnt = " << cnt << endl;

    multiset<int>::iterator it = number.find(7);
    if(it == number.end())
    {
        cout << "该元素不存在multiset中" << endl;
    }
    else
    {
        cout << "该元素存在multiset中 " << *it << endl;
    }

    cout << endl << "multiset的bound系列函数" << endl;
    auto pos = number.lower_bound(8);
    auto pos2 = number.upper_bound(8);
    cout << "*pos = " << *pos << endl;
    cout << "*pos2 = " << *pos2 << endl;
    while(pos != pos2)
    {
        cout << *pos << "  ";
        ++pos;
    }
    cout << endl;

    pair<multiset<int>::iterator, multiset<int>::iterator> ret2 = 
        number.equal_range(8);
    while(ret2.first  != ret2.second)
    {
        cout << *ret2.first << "  ";
        ++ret2.first;
    }
    cout << endl;

    cout << endl << "multiset的insert操作" << endl;
    multiset<int>::iterator ret = number.insert(4);
    display(number);

    cout << endl << endl;
    vector<int> vec = {1, 7, 11, 33, 22, 6};
    number.insert(vec.begin(), vec.end());
    display(number);

    cout << endl << endl;
    number.insert({10, 40, 20, 70});
    display(number);

    cout <<endl << "multiset的erase操作" << endl;
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

