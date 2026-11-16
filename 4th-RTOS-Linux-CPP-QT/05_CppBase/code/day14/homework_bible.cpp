#include <iostream>
#include <map>
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
//学完了map之后，不需要使用record了
//pair的功能和record的功能是一模一样的
//
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
                    //每一个单词
                    //利用map的下标去访问的时候，如果没有在map中，会自动插入到map中
                    //key是word，value值是什么呢？？？？当前数据类型的零值0
                    ++_dict[word];
                }
            }
        }
    }
    void store(const std::string &filename){
        //文件输出流
        ofstream ofs(filename);
        //遍历map的方式
        auto it1 = _dict.begin();
        auto it2 = _dict.end();
        while(it1 != it2){
            //迭代器目前阶段就可以把它理解为是指针一样
            //指针指向了元素，也就是record
            ofs << it1->first << " " << it1->second << endl;
            ++it1;
        }
        ofs.close();
    }
private:
    map<string,int> _dict;
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

