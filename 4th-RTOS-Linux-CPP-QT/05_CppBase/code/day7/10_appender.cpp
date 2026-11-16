#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
using std::cout;
using std::endl;
using namespace log4cpp;

void test(){
    //ostreamAppender
    //希望输出到标准输出流，也就是控制台 cout
    //创建了一个堆区的对象，使用了一个栈变量指针去指向该对象的地址
    OstreamAppender * ap1 = new OstreamAppender("console", &cout);
    //Layout其实就是格式化器 时间日期等格式化输出的组件
    //使用指针来进行操作，实际上便是OstreamAppender对象关联了layout
    ap1->setLayout(new BasicLayout());
    //利用Category的静态成员函数，创建了一个Category对象
    //使用了引用来接收，避免了拷贝的过程
    Category & root = Category::getRoot();
    //setAppender和addAppender都可以，前者只可以设置一个，后者可以设置多个
    root.setAppender(ap1);
    //设置了一个优先级，只有高于DEBUG级别的日志才能够输出
    //这里面日志系统设置了一个级别优先级DEBUG，那么每一条日志也会有一个优先级
    //只有当日志的优先级高于日志系统的优先级时，才能够输出
    //河南省高考的分数线 600(相当于日志系统的优先级)
    //某个考生只有考的比600分更高才能够过线(某条日志的优先级)
    root.setPriority(Priority::INFO);
    //需要使用root日志记录器来去包装日志
    root.debug("this is a debug message");
    root.info("this is a info message");
    root.alert("this is an alert message");
    root.error("this is an error message");
}

void test2(){
    //设置文件输出器，输出的目的地为文件
    FileAppender * ap1 = new FileAppender("file", "wd.log");
    //设置格式化器
    ap1->setLayout(new BasicLayout());
    //获取日志记录器对象
    Category & root = Category::getRoot();
    //需要将这些组件关联在一起
    root.setAppender(ap1);
    root.setPriority(Priority::INFO);
    
    root.debug("this is a debug message");
    root.info("this is a info message");
    root.alert("this is an alert message");
    root.error("this is an error message");

}

int main()
{
    test2();
    return 0;
}

