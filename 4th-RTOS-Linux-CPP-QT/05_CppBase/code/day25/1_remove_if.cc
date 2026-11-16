#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::remove_if;
using std::for_each;
using std::vector;

bool func(int value)
{
    return value > 5;
}
void test()
{
    vector<int> vec = {1, 3, 7, 9, 5, 6, 3, 6};
    for_each(vec.begin(), vec.end(), [](int x){
             cout << x << "  ";
             });
    cout << endl;

    cout << endl << "执行remove_if之后的结果" << endl;
    /* //这一行代码是删除小于5的元素，与题意不合，写在此处的目的就是告诉我们 */
    /* //bind2nd也可以与less结合 */
    /* auto it = remove_if(vec.begin(), vec.end(), bind2nd(std::less<int>(), 5)); */

    auto it = remove_if(vec.begin(), vec.end(), bind2nd(std::greater<int>(), 5));
    /* auto it = remove_if(vec.begin(), vec.end(), bind1st(std::less<int>(), 5)); */

    /* auto it = remove_if(vec.begin(), vec.end(), [](int value)->bool{ */
    /*                     return value > 5; */
    /*                     }); */
    //remove_if并不能一次将满足条件的元素进行删除，但是会返回一个指向待删除元素的
    //首迭代器，然后配合着容器的erase操作，就可以将多余的元素删除掉
    /* auto it = remove_if(vec.begin(), vec.end(), func); */
    vec.erase(it, vec.end());

    for_each(vec.begin(), vec.end(), [](int x){
             cout << x << "  ";
             });
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

