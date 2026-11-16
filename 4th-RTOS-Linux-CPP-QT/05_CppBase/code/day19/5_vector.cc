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

void test()
{
    cout << "sizeof(vector<int>) = " << sizeof(vector<int>) << endl;
    cout << "sizeof(vector<long>) = " << sizeof(vector<long>) << endl;

    cout << endl;
    vector<int> number = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    display(number);

    cout << endl << "在vector的尾部进行插入与删除" << endl;
    number.push_back(100);
    number.push_back(200);
    display(number);
    number.pop_back();
    display(number);

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

