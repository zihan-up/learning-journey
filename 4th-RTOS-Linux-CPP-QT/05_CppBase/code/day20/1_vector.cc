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
    cout << "sizeof(vector<int>) = " << sizeof(vector<int>) << endl;
    cout << "sizeof(vector<long>) = " << sizeof(vector<long>) << endl;

    cout << endl;
    vector<int> number = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    display(number);
    printVectorCapacity(number);

    cout << endl << "在vector的尾部进行插入与删除" << endl;
    number.push_back(100);
    number.push_back(200);
    display(number);
    printVectorCapacity(number);
    number.pop_back();
    display(number);
    printVectorCapacity(number);

    cout << endl << "获取vector中第一个元素的首地址" << endl;
    &number;//error，不能得到第一个元素的首地址
    &*number.begin();//ok
    &number[0];//ok
    int *pdata = number.data();//pdata指针指向的就是第一个元素

    cout << endl << "在vector的任意位置进行插入" << endl;
    auto pos = number.begin();
    /* pos += 2;//ok */
    ++pos;
    ++pos;
    cout << "*pos = " << *pos << endl;
    number.insert(pos, 11);
    display(number);
    printVectorCapacity(number);
    cout << "*pos = " << *pos << endl;

    cout << endl;
    //vector在使用insert插入元素的时候，因为并不知道每次插入元素的个数，有可能
    //因为插入元素过多，导致底层发生扩容，这样迭代器会指向老的空间，如果此时
    //还使用指向老空间的迭代器，那么后续的操作都使用的是无效的迭代器，将这种
    //现象称为迭代器失效(本质就是因为底层发生了扩容导致的)
    //
    //解决方案：每次使用迭代器的时候，将迭代器进行重新置位
    pos = number.begin();
    pos += 2;
    cout << "*pos = " << *pos << endl;
    number.insert(pos, 5, 33);
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

    cout << endl;
    pos = number.begin();
    pos += 2;
    cout << "*pos = " << *pos << endl;
    number.insert(pos, {111, 777, 444});
    display(number);
    printVectorCapacity(number);
    cout << "*pos = " << *pos << endl;

    cout << endl << "vector中元素的清空" << endl;
    number.clear();//清空元素
    number.shrink_to_fit();//回收多余的空间
    cout << "size() = " << number.size() << endl;
    cout << "capacity() = " << number.capacity() << endl;
}

void test2()
{
    vector<int> number;
    cout << "000" << endl;
    number[0] = 10;//越界了
    /* number.at(0); */
    cout << "111" << endl;
}
int main(int argc, char *argv[])
{
    test();
    return 0;
}

