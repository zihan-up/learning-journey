#ifndef __Message_H__
#define __Message_H__

#include <string>

using std::string;

namespace wd
{

//枚举类型相比宏的优势，是可以做类型检查
enum TaskType
{
    TASK_TYPE_LOGIN_SECTION1 = 1,
    TASK_TYPE_LOGIN_SECTION1_RESP_OK,
    TASK_TYPE_LOGIN_SECTION1_RESP_ERROR, 
    TASK_TYPE_LOGIN_SECTION2,
    TASK_TYPE_LOGIN_SECTION2_RESP_OK,
    TASK_TYPE_LOGIN_SECTION2_RESP_ERROR,
};

struct TLV
{
    int type;
    int length;
    char data[1024];
};

struct Packet
{
    int type;
    int length;
    string msg;
};

}//end of namespace wd


#endif

