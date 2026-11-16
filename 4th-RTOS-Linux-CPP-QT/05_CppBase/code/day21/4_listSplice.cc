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

void test()
{
    list<int> number{1, 3, 7, 9};
    list<int> other{2, 6, 8, 4};
    display(number);
    display(other);

#if 0
    cout << endl << endl;
    auto it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;
    number.splice(it, other);
    display(number);
    display(other);
#endif
    cout << endl << endl;
    auto it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;
    auto pos = other.end();
    --pos;
    cout << "*pos = " << *pos << endl;
    number.splice(it, other, pos);
    display(number);
    display(other);

    cout << endl << endl;
    cout << "*it = " << *it << endl;
    pos = other.begin();
    cout << "*pos = " << *pos << endl;
    auto pos2 = other.end();
    --pos2;
    cout << "*pos2 = " << *pos2 << endl;
    number.splice(it, other, pos, pos2);
    display(number);
    display(other);

    cout << endl <<"splice在同一个链表中进行操作" << endl;
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;

    auto it2 = number.end();
    --it2;
    cout << "*it2 = " << *it2 << endl;
    number.splice(it, number, it2);
    display(number);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

