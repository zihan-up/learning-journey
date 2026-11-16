#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::remove_if;
using std::mem_fn;
using std::bind;

class Number
{
public:
    Number(size_t data = 0)
    : _data(data)
    {}

    void print() const
    {
        cout << _data << "  ";
    }

    bool isEven() const
    {
        return (0 == _data % 2);
    }

    bool isPrime() const
    {
        if(1 == _data)
        {
            return false;
        }

        for(size_t idx = 2; idx <= _data/2; ++idx)
        {
           if(0 == _data % idx)
            {
                return false;
            }
        }

        return true;
    }
private:
    size_t _data;
};

void test0()
{
    cout << endl <<"=====" << endl;
    Number num(10);
    auto f = mem_fn(&Number::print);
    f(num);
    
    cout << endl << endl;
    auto f2 = bind(&Number::print, &num);
    f2();
    cout << endl;

    cout << endl << endl;
    using namespace std::placeholders;
    auto f3 = bind(&Number::print, _1);
    f3(num);
    cout << endl;
}

void test()
{
    vector<Number> vec;
    for(size_t idx = 1; idx != 30; ++idx)
    {
        vec.push_back(Number(idx));
    }

    for_each(vec.begin(), vec.end(), mem_fn(&Number::print));
    /* Number num(10); */
    /* for_each(vec.begin(), vec.end(), bind(&Number::print, &num))//这行的写法达不到效果 */
    /* using namespace std::placeholders; */
    /* for_each(vec.begin(), vec.end(), bind(&Number::print, _1));//ok */
    cout << endl;

    //删除所有的偶数
    vec.erase(remove_if(vec.begin(), vec.end(), mem_fn(&Number::isEven))
              , vec.end());
    for_each(vec.begin(), vec.end(), mem_fn(&Number::print));
    cout << endl;
    
    //删除所有的质数
    vec.erase(remove_if(vec.begin(), vec.end(), mem_fn(&Number::isPrime))
              , vec.end());
    for_each(vec.begin(), vec.end(), mem_fn(&Number::print));
    cout << endl;

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

