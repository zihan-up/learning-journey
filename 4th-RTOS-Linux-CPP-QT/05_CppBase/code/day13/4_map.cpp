#include <iostream>
#include <map>
#include <string>
#include <utility>
using std::cout;
using std::pair;
using std::string;
using std::map;
using std::endl;
using std::make_pair;
//map的使用
void test(){
    map<int,string> stu = {
        //构造pair的三种方式
        {1, "张三"},
        pair<int,string>(2, "李四"),
        pair<int,string>(2, "王五"),
        make_pair<int,string>(3, "赵六"),
        make_pair<int,string>(4, "赵六")
    };
    //map遍历
   //利用size和下标来组合遍历的方式也是不可以使用的
   //增强for循环
    for(auto & ele: stu){
        //遍历出来的ele是什么？？？pair
        //遍历出来的数据key=2只有李四，没有王五
        //说明相同key的value值数据会直接忽略
        cout << ele.first << ":" << ele.second << endl;
    }
    //迭代器
    //it1是迭代器，指向的是map里面的元素，也就是pair
    auto it1 = stu.begin();
    auto it2 = stu.end();
    while(it1 != it2){
        cout << (*it1).first << ":" << it1->second << endl;
        ++it1;
    }
}
void checkCount(const map<int,string> & map, int key){
    size_t number = map.count(key);
    //number要么是1要么是0
    if(number == 1){
        cout << "查找到了该key值" << endl;
    }else {
        cout << "没有查找到key" << endl;
    }
}
void checkFind(const map<int,string> & map, int key){
    auto ite = map.find(key);
    if(ite != map.end()){
        cout << "查找到了对应的数据" << ite->first << ":" << ite->second << endl;
    }else {
        cout << "没有查找到对应的元素" << endl;
    }
}

void test2(){
    map<int,string> stu = {
        //构造pair的三种方式
        {1, "张三"},
        pair<int,string>(2, "李四"),
        pair<int,string>(2, "王五"),
        make_pair<int,string>(3, "赵六"),
        make_pair<int,string>(4, "赵六")
    };

    //count find 
    checkCount(stu, 1);
    checkCount(stu, 5);
    checkFind(stu, 1);
    checkFind(stu, 6);
}


void checkInsert(map<int,string> & stu, const pair<int,string> & s){
    //pair iterator-bool
    auto result = stu.insert(s);
    //result返回的结果是iterator和bool组合体(pair)
    //第二个参数bool表示的是插入是否成功
    //第一个参数表示的是指向当前元素的迭代器(指针) result.first得到的是迭代器
    //map里面的元素是pair
    //result.first->first 获取的是pair的key值（插入的key值）
    //result.first->second获取的是value值（插入的value值）
    if(result.second){
        cout << "插入成功" << 
            result.first->first << ":" << result.first->second << endl;
        cout << "插入成功" << 
            (*result.first).first << ":" << (*result.first).second << endl;
    }else {
        cout << "插入失败" << endl;
    }
}

void test3(){
    map<int,string> stu = {
        //构造pair的三种方式
        {1, "张三"},
        pair<int,string>(2, "李四"),
        pair<int,string>(2, "王五"),
        make_pair<int,string>(3, "赵六"),
        make_pair<int,string>(4, "赵六")
    };
    //返回的结果是一个pair
    checkInsert(stu, {9, "潘潘"});
}

void test4(){
    map<int,string> stu = {
        //构造pair的三种方式
        {1, "张三"},
        pair<int,string>(2, "李四"),
        pair<int,string>(2, "王五"),
        make_pair<int,string>(3, "赵六"),
        make_pair<int,string>(4, "赵六")
    };
    map<int,string> number2 = {{1,"beijing"},{18,"shanghai"}};
    stu.insert(number2.begin(), number2.end());
    for(auto & ele : stu){
        cout << ele.first << ":" << ele.second << endl;
    }

    stu.insert({{7, "长风"},{8, "天明"}});
    for(auto & ele : stu){
        cout << ele.first << ":" << ele.second << endl;
    }
}
//map的下标和vector、string等的下标表示的含义是不同的
//map的下标指的是key的值，所以不仅可以传递数字，还可以传递其他数据类型
//调用了map[]下标操作之后，如果该下标的key值存在于map中直接返回
//如果该key值没有存在于map中，直接插入进去
//此时插入进去的value值是当前数据类型的零值
//通过下标也是可以取修改值的
void test5(){
    map<int,string> stu = {
        //构造pair的三种方式
        {1, "张三"},
        pair<int,string>(2, "李四"),
        pair<int,string>(2, "王五"),
        make_pair<int,string>(3, "赵六"),
        make_pair<int,string>(4, "小七")
    };
    cout << stu[0] << endl;
    cout << stu[3] << endl;
    cout << "=====================" << endl;
    for(auto & ele : stu){
        cout << ele.first << ":" << ele.second << endl;
    }
    cout << "=====================" << endl;
    stu[0] = "sssss";
    stu[3] = "xxxxxx";
    for(auto & ele : stu){
        cout << ele.first << ":" << ele.second << endl;
    }

}


int main()
{
    test5();
    return 0;
}

