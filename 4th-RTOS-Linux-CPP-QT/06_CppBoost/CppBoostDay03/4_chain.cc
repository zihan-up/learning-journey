#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;

//提出薪资请求的类
class RaiseRequest
{
public:
    RaiseRequest(const string &name, int salary)
    : _name(name)
    , _salary(salary)
    {}

    string getName() const
    {
        return _name;
    }

    int getSalary() const
    {
        return _salary;
    }

    ~RaiseRequest()
    {}
private:
    string _name;//提出薪资申请的员工的名字
    int _salary;//提出加薪多少
};

//薪资审批者（抽象类）
class SalaryApprover
{
public:
    SalaryApprover()
    : _pNext(nullptr)
    {
    }

    //纯虚函数，如何处理加薪请求
    virtual void processRequest(const RaiseRequest &request) = 0;

    void setNextChain(SalaryApprover *pNext)
    {
        _pNext = pNext;
    }

    void sendRequestToNextHandler(const RaiseRequest &request)
    {
        if(_pNext)
        {
            _pNext->processRequest(request);//肯定也会体现多态
        }
        else
        {
            cout << request.getName() << "的加薪请求: "
                 << request.getSalary() << "元，没有人可以处理"
                 << endl;
        }
    }

private:
    SalaryApprover *_pNext;
};

class DepartmentManager
: public SalaryApprover
{
public:
    virtual void processRequest(const RaiseRequest &request) override
    {
        int salary = request.getSalary();
        if(salary <= 1000)
        {
            cout << request.getName() << "的加薪请求： "
                 << request.getSalary() << "元，被部门经理同意了"
                 << endl;
        }
        else
        {
            //如果部门经理处理不了，就将请求交给上一级进行处理
            sendRequestToNextHandler(request);
        }
    }
};

class CTO
: public SalaryApprover
{
public:
    virtual void processRequest(const RaiseRequest &request) override
    {
        int salary = request.getSalary();
        if(salary > 1000  && salary <= 10000)
        {
            cout << request.getName() << "的加薪请求： "
                 << request.getSalary() << "元，被CTO同意了"
                 << endl;
        }
        else
        {
            //如果CTO处理不了，就将请求交给上一级进行处理
            sendRequestToNextHandler(request);
        }
    }
};

class Manager
: public SalaryApprover
{
public:
    virtual void processRequest(const RaiseRequest &request) override
    {
        int salary = request.getSalary();
        if(salary > 10000  && salary <= 30000)
        {
            cout << request.getName() << "的加薪请求： "
                 << request.getSalary() << "元，被总经理同意了"
                 << endl;
        }
        else
        {
            //如果总经理处理不了，就将请求交给上一级进行处理
            sendRequestToNextHandler(request);
        }
    }
};

void test()
{
    //创建三个领导对象，分别是部门经理、CTO、总经理
    unique_ptr<SalaryApprover> pdm(new DepartmentManager());
    unique_ptr<SalaryApprover> pcto(new CTO());
    unique_ptr<SalaryApprover> pgm(new Manager());

    //四个加薪请求者对象
    RaiseRequest zhangsan("zhangsan", 800);
    RaiseRequest lisi("lisi", 2000);
    RaiseRequest wangwu("wangwu", 20000);
    RaiseRequest shiwan("shiwan", 100000);

    //将部门经理、CTO、总经理让他们形成一个链式结构
    pdm->setNextChain(pcto.get());
    pcto->setNextChain(pgm.get());
    pgm->setNextChain(nullptr);

    //四个申请者都提出自己的请求
    pdm->processRequest(zhangsan);
    pdm->processRequest(lisi);
    pdm->processRequest(wangwu);
    pdm->processRequest(shiwan);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

