#include <iostream>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <string>
using std::cout;
using std::endl;
using std::to_string;
using namespace log4cpp;

void test(){
    //先创建一个日志的输出目的地
    //第一个参数：可以随意取一个名字
    //第二个参数：设置的文件的名称
    //第三个参数：maxFileSize就是单个文件的大小，如果文件的大小超过了设置的大小
    //那么便会滚动产生一个新的文件
    //第四个参数：maxBackUpIndex：备份文件的数目
    //wd.log文件，后续会不断滚动wd.log.1 wd.log.2.......wd.log.9
    //第五个参数：文件是否是追加的模式
    //第六个参数：文件创建者及文件所属的组所具有的权限
    //一般情况下，仅需要设置前四个参数即可
    RollingFileAppender * ap1 = new RollingFileAppender("roll","wd.log",
                                                        1024 * 1024, 9);
    ap1->setLayout(new BasicLayout());
    //获取日志的记录器
    Category & category = Category::getRoot();
    category.setPriority(Priority::INFO);
    category.setAppender(ap1);
    //如果i的值是1000，那么只有wd.log一个文件
    //如果i的值是10000，那么有wd.log.1和wd.log两个文件
    //且wd.log.1的数据更加久远一些;wd.log文件存储的是最新的数据
    //其实只需要改名即可
    //wd.log文件始终是最新的文件
    //wd.log.xx后面的数字越大，表示的是日志距离当前时间越久远
    for(int i = 0; i < 120000; ++i){
        //数字如何转换成字符串strign对象呢？
        category.debug("this is a debug message");
        category.info("this is a info message");
        category.notice("this is a notice message");
        category.warn("this is a warn message");
        category.error("this is an error message");
        category.crit("this is a crit message");
        category.alert("this is a alert message");
        category.fatal("this is a fatal message");

    }
}

int main()
{
    test();
    return 0;
}

