#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//int the begining,the holy god created the world....
//the ...  the ... the...
//最终：
//the 2000
//in 100
//begining 20
//holy 2
//....
//原数据是一篇文章，很多行的数据，每行又有很多的单词组成
//单词和单词之间使用空格来进行分割的
//希望解析到每一个一个的单词，对每个单词进行统计：
class Record
{
public:

    Record(string word, int frequency)
    :_word(word)
    ,_frequency(frequency)
    {

    }

	string _word;
	int _frequency;
};
//思路：逐个单词进行解析判断，如果发现不是字母，则直接返回时false
//如果全部都处理完毕之后，全部都是字母，则是字母
bool is_alpha(const string & word){
    auto it1 = word.begin();//指向首元素的迭代器
    auto it2 = word.end(); //指向尾后的迭代器
    while(it1 != it2){
        if(!isalpha(*it1)){//判断每一个字符究竟是否是字母，如果不是字母
            return false;   //直接返回false
        }
        it1++;
    }
    return true;//整个处理过程中都没有返回false，那么说明都是字母
}

class Dictionary
{
public:
    Dictionary(){
        _dict.reserve(100000);
    }

    void read(const std::string &filename){
        //首先需要创建一个文件输入流对象
        ifstream ifs(filename);
        if(!ifs){
            cerr << "file is not found" << endl;
            return;
        }
        string line;
        while(getline(ifs, line)){
            //再对每一行的数据进行分割成单个单词
            istringstream iss(line);
            string word;
            while(iss >> word){
                //解析出了每个单词
                //但是解析出的单词有可能是数字，我们不想要，只希望是纯粹的字母
                //先把数字剔除掉
                if(is_alpha(word)){
                    //如果是一个字母，那么进行后续的处理
                    //判断当前的这个单词有没有出现过
                    //如果没有出现，则下面的写法是没有问题的
                    //如果已经出现过这个单词，那么应该将其词频+1操作
                    int i = 0;
                    for(; i < _dict.size(); ++i){
                        if(_dict[i]._word == word){
                            //单词出现过
                            ++_dict[i]._frequency;
                            break;
                        }
                    }
                    //只有在整个for循环处理过程中都没进入到if语句的才有资格
                    //去执行push_back操作
                    //需要找出这个特征，该特征区别于其他的数据
                    //全程都没进入到if语句，那么最终i的值应该等于_dict.size()
                    if(i == _dict.size()){
                        _dict.push_back(Record(word, 1));
                    }
                }
            }
        }
    }
    void store(const std::string &filename){
        //文件输出流
        ofstream ofs(filename);
        //遍历vector三种方式都可以使用
        auto it1 = _dict.begin();
        auto it2 = _dict.end();
        while(it1 != it2){
            //迭代器目前阶段就可以把它理解为是指针一样
            //指针指向了元素，也就是record
            ofs << it1->_word << " " << it1->_frequency << endl;
            ++it1;
        }
        ofs.close();
    }
private:
    vector<Record> _dict;
};

void test(){
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("bible.txt");
}

int main()
{
    test();
    return 0;
}

