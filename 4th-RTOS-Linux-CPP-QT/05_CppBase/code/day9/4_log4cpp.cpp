#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;
//封装了一个案例
//用户可以指定一个日志记录器的名称，去创建一个指定的日志记录器
//使用这个日志记录器去记录特定的日志
//案例目前来说有一个问题那就是会多次绑定输出器
//使得输出的结果有些问题
//可以对其进行一个改进，让其前面的代码只执行一次
//log4cpp + 单例
Category & getCategory(const string & categoryName){
    OstreamAppender * ap1 = new OstreamAppender("cosole", &cout);
    PatternLayout * pl = new PatternLayout();
    pl->setConversionPattern("%d %c [%p] %m%n");
    ap1->setLayout(pl);
    Category & rootCategory = Category::getRoot();
    rootCategory.setAppender(ap1);
    rootCategory.setPriority(Priority::DEBUG);
    Category & category = rootCategory.getInstance(categoryName);
    return category;
}

void test(){
    //Category & goodsCategory = getCategory("goodsDepart");
    //goodsCategory.info("a info message");
    //goodsCategory.alert("an alert message");
    //goodsCategory.debug("a debug message");
    Category & orderCategory = getCategory("orderDepart");
    orderCategory.info("a info message");
    orderCategory.alert("an alert message");
    orderCategory.debug("a debug message");
}

int main()
{
    test();
    return 0;
}

