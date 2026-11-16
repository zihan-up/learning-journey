#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::istringstream;
using std::istream;
using std::ostream;
using std::endl;
using std::cin;
//依然是深拷贝
class String 
{
public:
    String()
    :_pstr(new char[1]())
    {}
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }

	String(const String & rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
    }

    ~String(){
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr;
        }
    }
    //标准的赋值运算符流程：4个步骤
    //1.自赋值判断
    //2.回收左操作数原先申请的堆空间  s1 = s2; s1就是左操作数
    //s1.operator=(s2);
    //3.执行深拷贝阶段
    //4.返回对象
    String &operator=(const String & rhs){
        cout << "operator=(const String &)" << endl;
        if(this != &rhs){
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }
    // s1 = "hello";
    String &operator=(const char * pstr){
        cout << "operator=(const char *)" << endl;
        String temp(pstr);
        *this = temp;
        return *this;
    }

    // s1 += s2;
    // hello += world ===> helloworld
    // 变化的是s1不变的的是s2
    // 谁调用该函数，谁的_pstr就会受到影响
    //1.判断右操作数是否为空字符串，如果是空字符串不处理
    //2.先申请一块临时的堆空间(利用左右操作数申请对应大小的堆空间)
    //3.执行字符串的拷贝、拼接过程
    //4.释放左操作数申请的堆空间
    //5.左操作数的指针需要去指向临时申请的堆空间
    //6.返回该对象即可
    String &operator+=(const String & rhs){
        //1
        if(rhs.size() != 0){
            //2
            char * temp = new char[strlen(_pstr) + strlen(rhs._pstr) + 1]();
            //3
            strcpy(temp, _pstr);
            strcat(temp, rhs._pstr);
            //4.
            delete [] _pstr;
            //5;
            _pstr = temp;
        }
        return *this;
    }
    //s1 += "hello";
    String &operator+=(const char * pstr){
        String temp(pstr);
        *this += temp;
        return *this;
    }
	
    //为什么会有俩个？？？
    //一个是可以修改下标的值，一个是不可以修改下标的值
    //对于一个const对象来说，只可以调用第二个
    char &operator[](std::size_t index){
        if(index >= size()){
            static char nullchar = '\0';
            return nullchar;
        }
        return _pstr[index];
    }
    const char &operator[](std::size_t index) const{
        if(index >= size()){
            static char nullchar = '\0';
            return nullchar;
        }
        return _pstr[index];
    }
	
    std::size_t size() const{
        return strlen(_pstr);
    }
    const char* c_str() const{
        return _pstr;
    }
	
	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);
	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);
	
	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);

private:
	char * _pstr;
};
//输出流运算符
ostream & operator<<(ostream & os, const String & s){
    os << s._pstr;
    return os;
}
//输入流运算符
//希望结束的标志位是\n
istream & operator>>(istream & is, String & s){
    //is >> s._pstr;
    char c;
    vector<char> vec;
    //每次去接收一个字符，只要不是换行符，那么持续不断去处理
    while((c = is.get()) != '\n'){
        vec.push_back(c);
    }
    //录入过程结束
    //还需要将s原先的堆空间回收
    delete [] s._pstr;
    //申请堆空间，将vec里面的数据填充到堆空间对应的区域
    s._pstr = new char[vec.size() + 1]();
    for(int i = 0; i < vec.size(); ++i){
        //一个一个进行赋值操作
        s._pstr[i] = vec[i];
    }
    return is;
}
//进一步复用+=运算符
String operator+(const String & lhs, const String & rhs){
    String temp(lhs);
    temp += rhs;
    return temp;
}
String operator+(const String & lhs, const char * pstr){
    String temp(lhs);
    temp += pstr;
    return temp;
}
String operator+(const char * pstr, const String & rhs){
    String temp(pstr);
    temp += rhs;
    return temp;
}

//下面几个函数的套路全部都是一样的
//使用strcmp来进行比较
bool operator==(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) == 0;
}
bool operator!=(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) != 0;
}
bool operator<(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}
bool operator>(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}
bool operator<=(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}
bool operator>=(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}
	
void test(){
    String s1("hello");
    String s2("world");
    s1 = s2;
    cout << "=========" << endl;
    s1 = "hello,python";
}
void test2(){
    String s1("hello");
    cout << s1 << endl;
    String s2("world");
    cout << s2 << endl;
    s1 += s2;
    cout << s1 << endl;
    cout << "=================" << endl;

    s2 += "hello";
    cout << s2 << endl;
}

void test3(){
    String s = "hello";
    cout << s[1] << endl;
    s[1] = 'E';
    cout << s[1] << endl;
    const String s2 = "hello,world";
    cout << s2[0] << endl;
    //s2[0] = 'H';error
}

void test4(){
    String s;
    cin >> s;
    cout << s << endl;
}
void test5(){
    istringstream iss("hello,world");
    for(int i = 0; i < 11; ++i){
        char c = iss.get();
        cout << c << endl;
    }
}
void test6(){
    String s1 = "hello";
    String s2 = "world";
    String s3 = s1 + s2;
    cout << s3 << endl;
    String s4 = "hello" + s3;
    String s5 = s4 + "world";
    cout << s4 << endl;
    cout << s5 << endl;
}
int main()
{
    test6();
    return 0;
}

