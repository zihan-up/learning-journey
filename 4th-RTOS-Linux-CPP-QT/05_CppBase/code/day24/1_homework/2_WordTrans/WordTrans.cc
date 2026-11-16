#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::ifstream;
using std::istringstream;

class WordTrans
{
public:
    void buildMap(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            std::cerr << "open file " << filename << " error!" << endl;
            return;
        }

        string line;
        string key;
        while(ifs >> key, getline(ifs, line))
        {
            if(line.size() > 1)
            {
                _um[key] = line.substr(1);//对line取子串
                /* _um.insert({key, line.substr(1)}); */
            }
        }

        ifs.close();
    }

    void trans(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            std::cerr << "open file " << filename << " error!" << endl;
            return;
        }

        string line;
        while(getline(ifs, line))
        {
            istringstream iss(line);
            string word;
            while(iss >> word)
            {
                auto it = _um.find(word);

                if(it != _um.end())
                {
                    cout << it->second;
                }
                else
                {
                    cout << word;
                }
                cout << " ";
#if 0
                size_t cnt = _um.count(word);
                if(1 == cnt)
                {
                    cout << _um[word];
                }
                else
                {
                    cout << word;
                }
#endif
            }
            cout << endl;
        }

        ifs.close();
    }
private:
    unordered_map<string, string> _um;
};
void test()
{
    WordTrans wt;
    wt.buildMap("map.txt");
    wt.trans("file.txt");
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

