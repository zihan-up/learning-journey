#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
//sso:短字符串优化
//长度小于等于15，字符串和string存储在一起的
//长度大于15，那么字符串存储在堆区的
class String {
public:
    String(const char * pstr)
    :_size(strlen(pstr))
    {
        if(_size <= 15){
            //使用array
            //数组全部初始化为0
            memset(_buffer._local, 0, sizeof(_buffer._local));
            strcpy(_buffer._local, pstr);
        }else {
            //使用指针
            _buffer._pointer = new char[strlen(pstr) + 1]();
            strcpy(_buffer._pointer, pstr);
        }
    }
    ~String(){
        if(_size > 15){
            if(_buffer._pointer){
                delete [] _buffer._pointer;
                _buffer._pointer = nullptr;
            }
        }
    }
    //拷贝构造函数
    String(const String & rhs)
    :_size(rhs._size)
    {
        if(_size <= 15){
            memset(_buffer._local, 0, sizeof(_buffer._local));
            strcpy(_buffer._local, rhs._buffer._local);
        }else {
            _buffer._pointer = new char[rhs.size() + 1]();
            strcpy(_buffer._pointer, rhs._buffer._pointer);
        } 
    }
    //赋值运算符函数
    //s1 = s2;
    //左15以内，右15以内
    //左15以内，右15以外
    //左15以外，右15以内
    //左15以外，右15以外
    String & operator=(const String & rhs){
        if(this != &rhs){
            //如果左操作数在15以及15以内，使用local
            if(_size <= 15){
                //左操作数的数据清空
                memset(_buffer._local, 0, sizeof(_buffer._local));
            }else {
                delete [] _buffer._pointer;
            }
            //分析右操作数
            if(rhs.size() <= 15){
                //左边被赋值了之后肯定会使用local来进行存储
                strcpy(_buffer._local, rhs._buffer._local);
            }else {
                _buffer._pointer = new char[rhs.size() + 1]();
                strcpy(_buffer._pointer, rhs._buffer._pointer);
            }
        }
        _size = rhs._size;
        return *this;
    }

    char & operator[](size_t idx){
        if(idx >= size()){
            static char nullchar = '\0';
            return nullchar;
        }
        if(_size <= 15){
            return _buffer._local[idx];
        }else {
            return _buffer._pointer[idx];
        }
    }

    int size() const{
        return _size;
    }

    friend
    ostream & operator<<(ostream & os,const String & rhs);
private:
	union Buffer{
		char * _pointer;
		char _local[16];
	};
	
    //当前字符串的长度
	size_t _size;
    //
	size_t _capacity;
    //每次选择使用指针还是使用数组
    Buffer _buffer;
};

ostream & operator<<(ostream & os,const String & rhs){
    if(rhs._size <= 15){
        os << rhs._buffer._local;
    }else {
        os << rhs._buffer._pointer;
    }
    return os;
}
void test(){
    String s("hello");
    cout << s << ":" <<s.size() << endl;
    String s2("hello,world,hello,python");
    cout << s2 << ":" <<s2.size() << endl;

    cout << "================" << endl;
    String s3("hello,world");
    String s4 = s3;
    cout << s4 << endl;
    String s5("hellollllllllllllllllllll");
    String s6 = s5;
    cout << s6 << endl;
}
void test2(){
    String s1("hello");
    String s2("world");

    String s3("helllllllllllllllllllllllll");
    String s4("ppppppppppppppppppppppppppppp");
    //左15以内，右15以内
    //s1 = s2;
    //cout << s1 << endl;
    //左15以内，右15以外
    //s2 = s4;
    //cout << s2 << endl;
    //左15以外，右15以内
    //s3 = s1;
    //cout << s3 << endl;
    //左15以外，右15以外
    s3 = s4;
    cout << s3 << endl;
}
void test3(){
    String s("hello");
    cout << s[0] << endl;
    s[0] = 'W';
    cout << s[0] << endl;
    String s2("hellopppppppppppppppppppp");
    cout << s2[0] << endl;
    s2[0] = 'W';
    cout << s2[0] << endl;
}

int main()
{
    test3();
    return 0;
}

