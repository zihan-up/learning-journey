#include "logger.h"
//静态指针数据成员先进行初始化
Logger * Logger::_pInstance = nullptr;
Category * Logger::_root = nullptr;

//思路：
//1.需要将构造函数私有化，防止用户任意的调用
//2.暴露公有的静态成员函数，将创建的对象暴露出去
//如果有的话则返回暴露出去，如果没有的话则创建一个
//3.拷贝构造、赋值删除、析构函数私有

//构造函数只会被调用一次
Logger::Logger(){
   //如果只是单纯的单例，构造函数中没有太多的逻辑
   OstreamAppender * ap1 = new OstreamAppender("console", &cout);
   PatternLayout * pl = new PatternLayout();
   pl->setConversionPattern("%d %c [%p] %m%n");
   ap1->setLayout(pl);

   Category & root = Category::getRoot();
   root.setAppender(ap1);
    root.setPriority(Priority::DEBUG);
    //对指针数据成员进行赋值操作
    _root = &root;
}
//实现2里面的功能
Logger * Logger::getInstance(){
    if(_pInstance == nullptr){
        _pInstance = new Logger();
    } 
    return _pInstance;
}
Logger::~Logger(){
    //在早些版本，需要调用该函数去完成堆对象的回收工作
    //但是现在即便不写也没有内存泄漏问题
    Category::shutdown();
}
//潜在的风险点：
//不能提前调用destroy函数
void Logger::destroy(){
    if(_pInstance){
        delete _pInstance;
        _pInstance = nullptr;
    }
}
//把这几部分拼接在一起即可
//但是需要注意一点的是字符串的拼接 const char *不可以使用+号
//使用string是可以使用+的
void Logger::warn(const char * file, int line, const char * func, const char * msg){
    string content = file + std::to_string(line) + func + msg;
    _root->warn(content);
}
void Logger::error(const char * file, int line, const char * func, const char * msg){
    string content = file + std::to_string(line) + func + msg;
    _root->error(content);
}
void Logger::debug(const char * file, int line, const char * func, const char * msg){
    string content = file + std::to_string(line) + func + msg;
    _root->debug(content);
}
void Logger::info(const char * file, int line, const char * func, const char * msg){
    string content = file + std::to_string(line) + func + msg;
    _root->info(content);
}
