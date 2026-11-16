#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

struct CompareList
{
    bool operator()( const int& lhs, const int& rhs ) const
    {
        cout << "struct CompareList" << endl;
        return lhs > rhs;
    }
};

void test()
{
    list<int> number = {1, 3, 3, 3, 5, 8, 9, 7, 4, 3, 2};
    display(number);

    cout << endl << "list的unique函数" << endl;
    number.unique();
    display(number);

    cout << endl << "list的reverse函数" << endl;
    number.reverse();//链表的逆置
    display(number);

    cout << endl << "list的sort函数" << endl;
    number.sort();//默认会按照从小到大进行排序
    /* std::less<int> lt; */
    /* number.sort(lt); */
    /* number.sort(std::less<int>()); */
    /* number.sort(std::greater<int>()); */
    /* number.sort(CompareList()); */
    display(number);

    cout << endl << "list的unique函数" << endl;
    number.unique();
    display(number);

    cout << endl << "list的merge操作" << endl;
    list<int> other = {33, 6, 11, 22};
    other.sort();
    display(other);
    number.merge(other);
    display(number);
    display(other);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

