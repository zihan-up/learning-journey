#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
using std::cout;
using std::endl;
using namespace log4cpp;
//日志记录器的功能
void test(){
    OstreamAppender * ap1 = new OstreamAppender("console", &cout);
    PatternLayout * pl = new PatternLayout();
    pl->setConversionPattern("%d %c [%p] %m%n");
    ap1->setLayout(pl);

    //先获取根日志记录器
    Category & root = Category::getRoot();
    //再根日志记录器中配置好
    //叶子记录器会直接继承根记录器的的配置
    root.setAppender(ap1);
    root.setPriority(Priority::INFO);
    //可以利用根日志记录器再去获取叶子记录器
    //这里面的goods user order其实就是%c的来源
    //后续商品模块的日志全部都使用goodsCategory去输出
    Category & goodsCategory = root.getInstance("goods");
    //后续用户模块的所有日志全部都使用userCategory去输出
    Category & userCategory = root.getInstance("user"); 
    //后续订单模块的所有日志全部都去使用orderCategory去输出
    Category & orderCategory = root.getInstance("order");
    goodsCategory.info("info message");
    userCategory.info("infos message");
    orderCategory.info("info message");


    Category::shutdown();
}

int main()
{
    test();
    return 0;
}

