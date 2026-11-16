#include <iostream>
#include <set>
#include <utility>
#include <string>
using std::cout;
using std::set;
using std::string;
using std::endl;
using std::pair;
//set的使用
void test(){
    //构造函数
    set<int> numbers;

    set<int> numbers2 = {1, 2, 3, 4, 4, 5};
    //迭代器
    set<int> numbers3(numbers2.begin(), numbers2.end());

    set<int> numbers4 = numbers3;
}
//set的迭代
void test2(){
    //1.set中不允许出现重复的元素
    //2.set中的元素默认会进行从小到大的顺序进行排序
    set<int> number = {1, 2, 3, 4, 4, 5, 6, 9, 8, 7};
    //cout << number[0] << endl;
    //1.增强for循环
    for(auto & ele : number){
        cout << ele << " ";
    }
    cout << endl;

    //2.迭代器
    auto it1 = number.begin();
    auto it2 = number.end();
    while(it1 != it2){
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;
}
//查找  
//count：返回的是个数；set不允许重复，所以要么是0要么是1
//find：返回的是迭代器，如果不是end尾后迭代器，那么说明找到了
void test3(){
    set<int> number = {1, 2, 3, 4, 4, 5, 6, 9, 8, 7};
    cout << number.count(1) << endl;
    cout << number.count(10) << endl;
    cout << "========================" << endl;
    //auto it = number.find(1);
    auto it = number.find(10);
    if(it != number.end()){
        cout << "查找到了元素:" << *it << endl;
    }else {
        cout << "没有查找到元素" << endl;
    }
}
void test4(){
    //先来看一下pair的使用
    pair<int,string> st1(1, "张三");
    //如何访问呢？？？？
    cout << st1.first << ":" << st1.second << endl;
}

void test5(){
    set<int> number = {1, 2, 3, 4, 4, 5, 6, 9, 8, 7};
    //返回的是一个pair<iterator,bool>
    //第二个参数表示是否插入成功
    //第一个参数表示的是插入成功或者阻止插入的这个元素的迭代器
    //auto result = number.insert(3);
    auto result = number.insert(10);
    if(result.second){
        cout << "insert success" << *result.first << endl;
    }else {
        cout << "insert fail:" << *result.first  <<endl;
    }
}

void test6(){
    set<int> number = {1, 2, 3, 4, 4, 5, 6, 9, 8, 7};
    set<int> number2 = {6, 9, 10, 11, 13};
    number.insert(number2.begin(), number2.end());
    for(auto & ele : number){
        cout << ele << " ";
    }
    cout << endl;

    number.insert({100,200,240});
    for(auto & ele : number){
        cout << ele << " ";
    }
    cout << endl;
}

int main()
{
    test6();
    return 0;
}

