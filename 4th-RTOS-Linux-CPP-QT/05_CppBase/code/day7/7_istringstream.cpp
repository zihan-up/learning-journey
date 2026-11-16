#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::string;
//字符串输入流的使用
void test(){
    string str = "123 456";
    //将字符串进行分割处理，默认的分隔符是空格、换行符、制表符
    istringstream iss(str);
    int number;
    while(iss >> number){
        cout << number << endl;
    }
}
//昨天的圣经作业:
void test2(){
    string line = "1   in the beginning hello god created the heaven and the earth";
    istringstream iss(line);
    string word;
    while(iss >> word){
        cout << word << endl;
    }
}
class Config{
public:
    Config(const string & key, const string & value)
    :_key(key)
    ,_value(value)
    {

    }

    string _key;
    string _value;
};
//该类的对象需要有多个嘛？？？？单例即可
class AliyunConfig{
public:
    static AliyunConfig * getInstance(){
        if(_ps == nullptr){
            _ps = new AliyunConfig();
        }
        return _ps;
    }

    static void destroy(){
        if(_ps){
            delete _ps;
            _ps = nullptr;
        }
    }

    //需要存放键值对信息
    //需要填充vector
    //还可以进一步优化：
    //如果之前已经存放过了当前key值，那么此时应该如何操作呢？？更新还是忽略
    //目前的逻辑没有考虑到key值相同的情况下的处理情况，会存储多份
    void put(string key, string value){
        Config config(key, value);
        _configPairs.push_back(config);
    }
    //利用key获取value值，比如输入ip得到192.168.120.110等
    //比如输入port得到8080
    //需要用到vector的遍历
    string get(string key){
        for(int i = 0; i < _configPairs.size(); ++i){
            if(_configPairs[i]._key == key){
                return _configPairs[i]._value;
            }
        }
        string s;
        return s;
    }

private:
    AliyunConfig()
    {
        _configPairs.reserve(8);
    }
    vector<Config> _configPairs;
    static AliyunConfig * _ps;
};
AliyunConfig * AliyunConfig::_ps = nullptr;


//用在配置文件中
//aliyun.conf
//ip 192.168.125.130
//port 8080
void test3(){
    //读取配置文件里面的配置信息，解析
    //使用输入流还是输出流？？？文件输入流
    ifstream ifs("aliyun.conf");
    if(!ifs){
        cerr << "this file is not found" << endl;
        return;
    }
    //接下来应该如何处理？？？？？
    //line其实就是一组键值对的组合
    //需要将这个字符串分割成两部分，分别是key和value
    string line;
    while(getline(ifs, line)){
        istringstream iss(line);
        string key, value;
        iss >> key >> value;
        AliyunConfig::getInstance()->put(key, value);
    }
    //处理到这，其实已经获取到了所需要的键值对的值
    //希望可以和单例结合在一起
    cout << AliyunConfig::getInstance()->get("ip") << endl;
    cout << AliyunConfig::getInstance()->get("port") << endl;

    AliyunConfig::destroy();
}

int main()
{
    test3();
    return 0;
}

