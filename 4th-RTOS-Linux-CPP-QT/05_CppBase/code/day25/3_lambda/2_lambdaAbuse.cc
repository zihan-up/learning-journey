#include <iostream>
#include <functional>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::function;
using std::vector;
using std::string;

vector<function<void(const string &)>> vec;

void test()
{
    int num = 100;
    string name("wangdao");
    /* function<void(const string &)> f = [&num, &name](const string &value){ */
    /*               cout << "num = " << num << endl; */
    /*               cout << "name = " << name << endl; */
    /*               cout << "value = " << value << endl; */
    /*               }; */
    /* vec.push_back(f); */
    /* vec.push_back([&num, &name](const string &value){ */
    vec.push_back([num, name](const string &value){
                  cout << "num = " << num << endl;
                  cout << "name = " << name << endl;
                  cout << "value = " << value << endl;
                  });

    /* for(auto &elem : vec) */
    /* { */
    /*     elem("hello"); */
    /* } */
}

void test2()
{
    for(auto &elem : vec)
    {
        elem("hello");
    }
}

int main(int argc, char *argv[])
{
    test();
    test2();
    return 0;
}

