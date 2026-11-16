#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

using std::cout;
using std::endl;
using std::list;
using std::unordered_map;
using std::pair;

class LRU
{
public:
    LRU(size_t capa)
    : _capacity(capa)
    {
    }

    void put(int key, int value)
    {
        auto it = _cache.find(key);
        //如果key是存在的
        if(it != _cache.end())
        {
            //更新value
            it->second->second = value;
            //交换位置
            _nodes.splice(_nodes.begin(), _nodes, it->second);
        }
        else//key值是不存在
        {
            //如果是满的
            if(_capacity == _nodes.size())
            {
                //获取list的最后一个元素
                auto deleteNode = _nodes.back();
                //将元素从list中删除
                _nodes.pop_back();
                //将元素从unordered_map中删除
                _cache.erase(deleteNode.first);
            }
            //将key与value放在list的头部
            _nodes.push_front({key, value});
            //将key以及key在list中的位置存放在unordered_map
            /* _cache.insert({key, _nodes.begin()}); */
            _cache[key] =  _nodes.begin();
        }
    }

    int get(int key)
    {
        auto it = _cache.find(key);
        if(it != _cache.end())
        {
            //更新元素在list中的位置（最近访问的）
            _nodes.splice(_nodes.begin(), _nodes, it->second);
            return it->second->second;
        }
        else
        {
            return -1;
        }
    }

    void display() const
    {
        for(auto &elem : _nodes)
        {
            cout << "(" << elem.first
                 << ", " << elem.second
                 << ")" << "  ";
        }
        cout << endl;
    }
private:
    //容量含义
    size_t _capacity;
    //使用list存储key与value
    list<pair<int, int>> _nodes;
    //通过key找到key在list中的位置值
    unordered_map<int, list<pair<int, int>>::iterator> _cache;
};
void test()
{
    LRU lru(3);

    lru.put(1, 10);
    lru.display();

    cout << endl;
    lru.put(2, 20);
    lru.display();

    cout << endl;
    cout << "lru.get(1) = " << lru.get(1) << endl;
    lru.display();

    cout << endl;
    lru.put(3, 30);
    lru.display();

    cout << endl;
    lru.put(2, 22);
    lru.display();

    cout << endl;
    lru.put(4, 40);
    lru.display();

    cout << endl;
    cout << "lru.get(1) = " << lru.get(1) << endl;
    lru.display();

    cout << endl;
    cout << "lru.get(2) = " << lru.get(2) << endl;
    lru.display();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

