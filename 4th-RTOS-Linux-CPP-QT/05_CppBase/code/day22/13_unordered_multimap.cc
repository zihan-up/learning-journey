#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::unordered_multimap;
using std::string;
using std::pair;
using std::make_pair;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem.first << "  "
             << elem.second << endl;
    }
}

void test()
{
    //unordered_multimap的基本特征
    //1、存放的是key-value类型，key值是不唯一的，可以重复；但是value值既可以
    //重复，也可以不重复
    //2、key值是没有顺序的
    //3、底层使用的是哈希
    unordered_multimap<int, string> number = {
        pair<int, string>(2, "beijing"),//1、使用std::pair构建pair对象
        pair<int, string>(3, "wuhan"),
        make_pair(6, "shanghai"),//2、使用make_pair函数的返回结构构建pair
        make_pair(7, "shenzhen"),
        {5, "tianjin"},//3、使用大括号构建pair类型
        {1, "beijing"},
        {1, "hubei"},
    };
    display(number);

    cout <<endl << "unordered_multimap的查找" << endl;
    size_t cnt = number.count(6);
    cout << "cnt = " << cnt <<endl;

    unordered_multimap<int, string>::iterator it = number.find(4);
    if(it != number.end())
    {
        cout <<"该元素存在unordered_multimap中" 
             << it->first << "   " 
             << it->second << endl;
    }
    else
    {
        cout << "该元素不存在unordered_multimap中" << endl;
    }

    cout <<endl << "unordered_multimap的insert操作" << endl;
    number.insert(pair<int, string>(8, "wangdao"));
    /* number.insert(make_pair(8, "wangdao")); */
    /* number.insert({8, "wangdao"}); */
    display(number);

    cout <<endl << "unordered_multimap的删除" << endl;
    number.erase(5);
    display(number);

#if 0
    cout << endl << "unordered_multimap的下标" << endl;
    cout << "number[3] = " << number[3] << endl;//查找
    cout << "number[4] = " << number[4] << endl;//插入
    display(number);

    cout << endl;
    //T &operator[](const Key &key)
    number[4] = "dongjing";//修改
    number[2] = "wangdao";
    number.operator[](2).operator=("wangdao");
    display(number);

    cout << endl;
    const unordered_multimap<int, int> tmp = {{1, 3}};
    /* tmp[1] = 2;//error,unordered_multimap的下标访问运算符是没有重载const版本，所以 */
               //const对象不能使用下标操作
    /* cout << "tmp[1] = " << tmp[1] << endl; */
#endif
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

