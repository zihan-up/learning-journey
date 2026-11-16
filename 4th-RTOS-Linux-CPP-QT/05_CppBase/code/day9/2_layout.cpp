#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
using std::cout;
using std::endl;
using namespace log4cpp;

//layout的使用
void test(){
    //介绍日志设置双目的地 不仅可以向控制台输出还可以向日志文件输出
    OstreamAppender * ap1 = new OstreamAppender("console", &cout);
    FileAppender * ap2 = new FileAppender("file", "layout.log");
    //new/delte需要成对出现
    //在ap1和ap2中如果同时关联pl那么后续进行回收的时候就会出现问题
    //出现double free的问题
    PatternLayout * pl = new PatternLayout();
    PatternLayout * pl2 = new PatternLayout();
    //格式化输出，ConversionPattern就是去设置具体的格式
    pl->setConversionPattern("%d %c [%p] %m%n");
    pl2->setConversionPattern("%d %c [%p] %m%n");
    //cout << "log1" << endl;
    ap1->setLayout(pl);
    ap2->setLayout(pl2);
    //cout << "log2" << endl;
    Category & category = Category::getRoot();
    //关联appender
    category.addAppender(ap1);
    category.addAppender(ap2);
    category.setPriority(Priority::INFO);
    category.debug("this is a debug message");
    category.info("this is a info message");
    category.notice("this is a notice message");
    category.warn("this is a warn message");
    category.error("this is an error message");
    category.crit("this is a crit message");
    category.alert("this is a alert message");
    category.fatal("this is a fatal message");
}

int main()
{
    test();
    return 0;
}

