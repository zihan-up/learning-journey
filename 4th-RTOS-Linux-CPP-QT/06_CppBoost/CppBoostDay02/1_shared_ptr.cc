#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;
using std::map;
using std::set;
using std::string;

void test()
{
    shared_ptr<int> sp(new int(10));

    string text;
    shared_ptr<vector<string>> file(new vector<string>);
    file->push_back(text);

    string word = "hello";
    map<string,  shared_ptr<set<size_t>>> wm;
    shared_ptr<set<size_t>> &lines = wm[word];
    if(!lines)
    {
        lines.reset(new set<size_t>);
    }
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

