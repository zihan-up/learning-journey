#include <iostream>
#include <deque>
#include <vector>

using std::cout;
using std::endl;
using std::deque;
using std::vector;

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
    deque<int> number = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    display(number);

    cout << endl << "在deque的尾部进行插入与删除" << endl;
    number.push_back(100);
    number.push_back(200);
    display(number);
    number.pop_back();
    display(number);

    cout << endl << "在deque的头部进行插入与删除" << endl;
    number.push_front(111);
    number.push_front(222);
    display(number);
    number.pop_front();
    display(number);

    cout << endl << "在deque的任意位置进行插入" << endl;
    auto pos = number.begin();
    /* pos += 2;//ok */
    ++pos;
    ++pos;
    cout << "*pos = " << *pos << endl;
    number.insert(pos, 11);
    display(number);
    cout << "*pos = " << *pos << endl;

    cout << endl;
    number.insert(pos, 5, 33);
    display(number);
    cout << "*pos = " << *pos << endl;

    cout << endl;
    vector<int> vec = {12, 34, 56, 78};
    number.insert(pos, vec.begin(), vec.end());
    display(number);
    cout << "*pos = " << *pos << endl;

    cout << endl;
    number.insert(pos, {111, 777, 444});
    display(number);
    cout << "*pos = " << *pos << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

