#include <iostream>
#include <vector>

using std::cout;
using std::endl;
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

void printVectorCapacity(const vector<int> &vec)
{
    cout << "size() = " << vec.size() << endl;
    cout << "capacity() = " << vec.capacity() << endl;
}
void test()
{
    vector<int> number = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    display(number);
    printVectorCapacity(number);

    cout << endl << "在vector的尾部进行插入与删除" << endl;
    number.push_back(100);
    number.push_back(200);
    display(number);
    printVectorCapacity(number);

    cout << endl << "在vector的任意位置进行插入" << endl;
    auto pos = number.begin();
    pos += 2;//ok
    cout << "*pos = " << *pos << endl;
    number.insert(pos, 11);
    display(number);
    printVectorCapacity(number);
    cout << "*pos = " << *pos << endl;

    cout << endl;
    //size() = m = 13,capacity() = n = 20,新插入的元素的个数t;
    //1、t < n - m;此时不会发生扩容
    //2、n - m < t < m;此时会按照2 * size进行扩容
    //3、n - m < t, m < t < n;会按照t + m进行扩容
    //4、n - m < t, t > n;会按照t + m进行扩容
    pos = number.begin();
    pos += 2;
    cout << "*pos = " << *pos << endl;
    number.insert(pos, 100, 33);
    display(number);
    printVectorCapacity(number);
    cout << "*pos = " << *pos << endl;

    cout << endl;
    vector<int> vec = {12, 34, 56, 78};
    pos = number.begin();
    pos += 2;
    cout << "*pos = " << *pos << endl;
    number.insert(pos, vec.begin(), vec.end());
    display(number);
    printVectorCapacity(number);
    cout << "*pos = " << *pos << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

