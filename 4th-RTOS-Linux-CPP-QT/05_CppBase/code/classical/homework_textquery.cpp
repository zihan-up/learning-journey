#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
using namespace std;

class TextQuery
{
public:
    //解析输入文件
    void readFile(const string & filename){
        //构建一个文件输入流对象
        ifstream ifs(filename);
        if(!ifs){
            cerr << "this file is not found" << endl;
            return;
        }
        //一行一行数据进行解析
        string line;
        //行号
        int lineNumber = 0;
        while(getline(ifs, line)){
            ++lineNumber;
            //将每一行的文章内容存储到vector中
            _lines.push_back(line);
            istringstream iss(line);
            string word;
            while(iss >> word){
                _wordLineNumbers[word].insert(lineNumber);
                ++_wordCount[word];
            }
        }
    }
    //查询指定的单词
    void query(const string & word){
        cout << "=========================" << endl;
        cout << word << " occurs " << _wordCount[word] << " times." << endl;
        for(auto & number : _wordLineNumbers[word]){
            cout << "(line" << number << ")" << _lines[number - 1] << endl;
        }
        cout << "=========================" << endl;
    }
private:
    //存储每一行的原始信息
    vector<string> _lines;
    //每个单词和对应的行号集合的映射关系
    map<string, set<int>> _wordLineNumbers;//the the
    //每个单词以及对应的次数
    map<string, int> _wordCount;
};



void test(){
    string queryWord("Shenzhen");

    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
}

int main()
{
    test();
    return 0;
}

