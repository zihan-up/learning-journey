#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::sort;

struct Record
{
    Record(const string &word, int frequency)
    : _word(word)
    , _frequency(frequency)
    {
    }

    string _word;
    int _frequency;
};

bool operator<(const Record &lhs, const Record &rhs)
{
    return lhs._word < rhs._word;
}

class Dictionary
{
public:
    Dictionary(int capa)
    {
        _dict.reserve(capa);
    }

    void read(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)//bool operator!(){}  operator bool() {}
        {
            //cout cerr clog
            cerr << "ifs open file " << filename << " error!" << endl;
            return;
        }

        string line;
        //while(ifs >> word)
        while(getline(ifs, line))
        {
            istringstream iss(line);//串IO，内存
            string word;

            //vector<Point> pt = {Point(1, 2), {3, 4}, (5, 6)};
            //逗号表达式
            /* while(iss >> word, !iss.eof())//word可能就是不规范abc123 */
            while(iss >> word)//word可能就是不规范abc123,while(真值表达式) iss  ---> bool /int
            {
                //newWord是处理之后的新单词
                string newWord = dealWord(word);

                //把新的单词插入到vector里面
                insert(newWord);
            }
        }

        //将元素进行排序
        sort(_dict.begin(), _dict.end());

        ifs.close();
    }

    //将单词与词频存储到文件中
    void store(const string &filename)
    {
        ofstream ofs(filename);
        if(!ofs)
        {
            cerr << "ofs open " << filename << " error" << endl;
            return;
        }

        for(size_t idx = 0; idx != _dict.size(); ++idx)
        {
            ofs << _dict[idx]._word << "   " 
                << _dict[idx]._frequency << endl;
        }

        ofs.close();
    }

    //对不符合要求的单词进行处理
    string dealWord(const string &word)
    {
        for(size_t idx = 0; idx != word.size(); ++idx)
        {
            //if(word[idx] > 'A')
            if(!isalpha(word[idx]))
            {
                return string();//以空串进行替换
            }
        }

        return word;
    }

    //把结果插入到vector中
    void insert(const string &word)
    {
        if(word == string())
        {
            return;
        }

        size_t idx = 0;
        for(idx = 0; idx != _dict.size(); ++idx)
        {
            if(word == _dict[idx]._word)
            {
                ++_dict[idx]._frequency;
                break;//记得写上
            }
        }

        if(idx == _dict.size())
        {
            _dict.push_back(Record(word, 1));
        }
    }

private:
    vector<Record> _dict;
};

int main(int argc, char **argv)
{
    Dictionary dictionary(13000);
    cout << "before reading..." << endl;
    time_t beg = time(NULL);
    dictionary.read("The_Holy_Bible.txt");
    time_t end  = time(NULL);
    cout << "time : " << (end - beg) << "s" << endl;
    cout << "after reading..." << endl;
    dictionary.store("dictVector.dat");
    return 0;
}

