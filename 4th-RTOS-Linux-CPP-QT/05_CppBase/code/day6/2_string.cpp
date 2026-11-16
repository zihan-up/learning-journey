#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//string的本质其实就是对于c风格字符串const char *进一层封装
//需要做的事情还是那么多，只不过现在有了string之后不需要开发者去做了
//而是string已经帮助我们做好了
void test(){
    //使用string，需要使用构造函数来创建一个string类对象
    //使用无参构造函数来创建s
    string s;//会用
    //数量 + 字符
    string s2(2, 'h');
    //使用c风格的字符串来创建string对象
    string s3("hello");//重点关注
    //使用hello的前3个字符来构建一个string对象
    string s4("hello", 3);
    string s5 = s4;
    string s6(s4);
    cout << s << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << s5 << endl;

    char str[6] = "hello";
    string s7(str, str + 6);//重点关注
                            //里面提及了一个概念，叫做iterator迭代器
                            //这一阶段大家就可以理解为是一个宽泛类型的指针
    cout << s7 << endl;
}

void test2(){
    //关于迭代器的详细介绍
    //目前阶段，大家就可以把迭代器当做指针去使用
    string s("hello");
    //这种写法其实有些过于复杂，在c++11的版本中引入了一个auto关键字
    //编译器可以自动去推断该变量的真实类型，所以强烈建议写成下面的形式
    //string::iterator i = s.begin();
    auto it1 = s.begin();
    auto it2 = s.end();
    cout << *it1 << endl;
    ++it1;
    cout << *it1 << endl;
}
//字符串的拼接操作
void test3(){
    //C风格的字符串应该如何处理？？？？ 堆区
    //const char * pstr1 = "hello";
    //const char * pstr2 = "world";
    //堆上申请一个空间，将pstr1和pstr2拷贝
    string s1("hello");
    string s2("world");
    //借助于一个append函数便可以完成上述这个功能
    s1.append(s2);
    cout << s1 << endl;
    //后续学习完运算符重载之后，可以知道下面这种写法的原理
    s1 += s2; //把string当做内置数据类型来使用
    cout << s1 << endl;
}

void test4(){
    //string类对象和c风格字符串之间是可以形成打通的
    //可以形成相互转换
    //c风格字符串转换成string对象
    string s("hello");
    const char * pstr = "world";
    string s2(pstr);
    //string对象转换成c风格字符串
    const char * pstr2 = s.c_str();
    const char * pstr3 = s.data();
    cout << pstr2 << pstr3 << endl;
    //判断字符串是否为空
    cout << s.empty() << endl;
    //统计字符串的长度 size和length均可以
    cout << s.size() << endl;
    cout << s.length() << endl;
    //字符串的末尾追加字符串
    s.push_back('h');//了解即可
    s.append("h");
    s += "h";
    cout << s << endl;
    //字符串的末尾添加追加另外一个字符串
    s.append(s2);
    cout << s << endl;
    //0表示的是起始位置索引号，3表示的是多少个字符
    s.append(s2, 0, 3);
    cout << s << endl;
}

void test5(){
    //find
    string s("hello");
    string s2("e");
    cout << s.find(s2) << endl;
    cout << s.find('e') << endl;
    cout << s.find("e") << endl;
}
//字符串的比较功能
void test6(){
    //字符串的比较：之前使用strcmp来进行比较
    //现在可以使用== != >= <= > <来进行比较
    string s1("hello");
    string s2("hello");
    string s3("world");
    cout << (s1 == s2) << endl;
    cout << (s1 == s3) << endl;
    cout << (s1 >= s2) << endl;
    cout << (s1 <= s3) << endl;
} 

void test7(){
    //字符串的遍历3种方式，全部都要掌握
    string s("hello");
    //方式1：下标访问运算符来进行操作
    //下标访问运算符的使用基类和数组的下标访问使用是一模一样的
    cout << s[0] << endl;
    for(int i = 0; i < s.size(); ++i){
        cout << s[i] << " ";
    }
    cout << endl;
    //方式2：增强for循环
    //for(数据类型 变量名称 : 需要遍历的变量){
    //  迭代出来的每个元素赋值给当前变量
    //}
    //为了避免这一次的拷贝操作，可以使用引用来去实现
    //关于数据类型，本案例中是char类型，其实可以使用auto来代替
    //编译器自动进行推断
    //for(char & c : s){
    for(auto & c : s){
        cout << c << " ";
    }
    cout << endl;
    //方式3：迭代器的方式
    auto it1 = s.begin();
    auto it2 = s.end();
    while(it1 != it2){
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;
}

class Computer{
public:
    Computer(const char * pstr, float price)
    :_brand(pstr)
    ,_price(price)
    {
        cout << "Computer(const char *,float)" << endl;
    }
    void print(){
        cout << "_brand=" << _brand << ",_price=" << _price << endl;
    }
    ~Computer(){
        cout << "~Computer()" << endl;
    }


private:
    string _brand;
    float _price;
};

void test8(){
    Computer c("Apple", 12000);
    c.print();

    //关于string 的使用
    string s = "hello";
}

int main()
{
    test8();
    return 0;
}

