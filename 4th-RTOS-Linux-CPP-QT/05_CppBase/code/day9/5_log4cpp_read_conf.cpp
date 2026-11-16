#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
using std::cout;
using std::endl;
//using namespace log4cpp;
//困惑点：里面的代码究竟执行了什么逻辑？为什么能够这么去写？
//究竟是如何实现的呢？？？？
//但是其实初学阶段这些内容如果想要搞懂，那么必须得需要阅读源码
//但是第三方类库编写的源码中充斥着大量的设计模式
//经常遇到的事情就是从入门到放弃
//关于源码的阅读建议是工作2年左右再去研究
//首先先会使用，后续再去研究原理
//能用即可，不求甚解

void test(){
    //需要读取的配置文件的名称以及位置
    std::string initFileName = "log4cpp.properties";
    //配置读取器读取配置文件里面的信息，进行正确的配置
	log4cpp::PropertyConfigurator::configure(initFileName);
    //得到根日志记录器
	log4cpp::Category& root = log4cpp::Category::getRoot();

    //得到叶子记录器
	log4cpp::Category& sub1 = 
		log4cpp::Category::getInstance(std::string("sub1"));

	log4cpp::Category& sub2 = 
		log4cpp::Category::getInstance(std::string("sub2"));

    //这里面并没有category设置appender以及设置priority的代码
    //为什么呢？因为在配置文件中已经进行了配置
    //读取配置文件中的信息，便可以得到这些配置关系
    //所以就无需在代码中进一步编写了

	root.warn("Storm is coming");

	sub1.debug("Received storm warning");
	sub1.info("Closing all hatches");

	sub2.debug("Hiding solar panels");
	sub2.error("Solar panels are blocked");
	sub2.debug("Applying protective shield");
	sub2.warn("Unfolding protective shield");
	sub2.info("Solar panels are shielded");

	sub1.info("All hatches closed");

	root.info("Ready for storm.");

    //可以写，也可以不写，这一步其实就是进行所有资源的回收工作
	log4cpp::Category::shutdown();
}

int main()
{
    test();
    return 0;
}

