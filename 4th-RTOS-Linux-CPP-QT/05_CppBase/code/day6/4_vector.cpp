#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
//vector的使用
void test(){
    //无参构造函数
    //注意：vector的写法和string有些不太一样
    //需要写一个<>里面标识的是当前vector里面存储的数据类型
    //可以是内置数据类型，也可以是自定义数据类型
    vector<int> number;
    // int arr[5];
    // 10表示的是vector里面初始化了10个int(0)，默认值便是当前数据类型的0值
    vector<int> numbers2(10);
    cout << numbers2[0] << endl;
    //10表示的是10个元素，30表示的是每个元素的值
    //vector里面存储了10个30
    vector<int> numbers3(10, 30);
    cout << numbers3[0] << endl;
    //初始化列表，其实就是大括号
    vector<int> numbers4{1, 2, 3, 4, 5};
    //使用迭代器的方式
    int arr[5] = {1, 2, 3, 4, 5};
    vector<int> numbers5(arr, arr + 5);
}

void test2(){
    vector<int> numbers{1, 2, 3, 4, 5};
    auto it1 = numbers.begin();
    auto it2 = numbers.end();
    cout << *it1 << endl;
    cout << numbers.empty() << endl;
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.push_back(6);
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
}

void test3(){
    //扩容
    vector<int> numbers;
    numbers.reserve(16);
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.push_back(1);
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.push_back(2);
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.push_back(3);
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.push_back(4);
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.push_back(5);
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.pop_back();
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.pop_back();//删除末尾的最后一个元素,但是操作过后容量没有收到影响
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.shrink_to_fit();//此时容量由16变成了3
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.push_back(10);
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
    numbers.clear();//size会收到影响，但是capacity不会受到影响
    cout << numbers.size() << endl;
    cout << numbers.capacity() << endl;
}

class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
    Point(const Point & rhs)
    :_x(rhs._x)
    ,_y(rhs._y)
    {
        cout << "Point(const Point & rhs)" << endl;
    }
    ~Point(){
        cout << "~Point()" << endl;
    }

private:
    int _x;
    int _y;
};
//无论vector里面有没有存放元素，其实大小始终是24字节
//24字节其实是3根指针的大小;
//一根指向开始;一根指向所存元素的末尾;一根指向当前容量的末尾
void test4(){
    vector<Point> vec;
    //cout << sizeof(vec) << endl;
    vec.reserve(16);//有提升
    vec.push_back(Point(1, 2));
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    vec.push_back(Point(1, 2));
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    vec.push_back(Point(1, 2));
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    vec.push_back(Point(1, 2));
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    vec.push_back(Point(1, 2));
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    //cout << sizeof(vec) << endl;
}
void test5(){
    vector<Point> vec;
    //cout << sizeof(vec) << endl;
    vec.reserve(16);//有提升
    //emplace_bakc表示的是会在vec所属的这块内存空间中，
    //调用对应的类的构造函数
    //创建对象，没有栈对象的创建过程
    vec.emplace_back(1, 2);
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    vec.emplace_back(1, 2);
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    vec.emplace_back(1, 2);
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    vec.emplace_back(1, 2);
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    vec.emplace_back(1, 2);
    cout << "size:" << vec.size() << ";capacity:" << vec.capacity() << endl;
    //cout << sizeof(vec) << endl;
}

void test6(){
    //vector的遍历
    vector<int> numbers{1, 2, 3, 4, 5, 6};
    //遍历方式1：利用下标来进行遍历
    for(size_t i = 0; i < numbers.size(); ++i){
        cout << numbers[i] << " ";
    }
    cout << endl;
    //遍历方式2：增强for循环
    //for(迭代出来的每个元素的类型  每个变量 ：需要迭代的容器)
    for(int & ele : numbers){
        cout << ele << " ";
    }
    cout << endl;
    //遍历方式3：迭代器的方式
    auto it1 = numbers.begin();
    auto it2 = numbers.end();
    while(it1 != it2){
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;
}

int main()
{
    test6();
    return 0;
}

