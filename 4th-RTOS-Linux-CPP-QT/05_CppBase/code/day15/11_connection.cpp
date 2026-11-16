#include <iostream>
using std::cout;
using std::endl;
//数据库：mysql oracle两个不同的数据库产品
//简化：连接、发送请求、返回响应、断开连接
//希望你开发一个产生（聚合终端），可以整合mysql、oracle的功能，
//提供一个统一的操作界面
//其他领域也需要类似的功能：商家的外卖平台、商家的聚合支付等等
//下面案例类比到商家的聚合支付，那么
//DBConnection类比为CombinePay
//MysqlConnection类比为AliPay
//OracleConnection类比为WechatPay
class DBConnection{
public:
    virtual void get() = 0;
    virtual void request() = 0;
    virtual void receive() = 0;
    virtual void close() = 0;
};
class MysqlConnection : public DBConnection{
public:
    virtual void get(){

    }
    virtual void request(){

    }
    virtual void receive(){

    }
    virtual void close(){

    }

};
class OracleConnection : public DBConnection{
public:
    virtual void get(){

    }
    virtual void request(){

    }
    virtual void receive(){

    }
    virtual void close(){

    }

};

//聚合数据库管理界面，聚合支付的界面
void process(DBConnection * db){
    db->get();

    db->request();

    db->receive();

    db->close();
}

void test(){
    MysqlConnection mysql;
    process(&mysql);
}

int main()
{
    test();
    return 0;
}

