#include "widget.h"

#include <QDebug>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_ptc = new Teacher;
    m_pst = new Student;

    //Qt4中的写法，该写法会将SIGNAL/SLOT中传递进来的当做字符串
    //进行处理，其实，传递任何不存在的都可以让编译通过，但是在运行
    //的时候，才能知道有没有出现问题，所以这种写法没有类型检测，
    //是不安全，不建议使用
    //connect(m_ptc, SIGNAL(treat()), m_pst, SLOT(eat()));
    //connect(m_ptc, SIGNAL(t2222()), m_pst, SLOT(e333()));

    //--------Qt5的版本---------
//    void (Teacher::*ptcArgVoid)() = &Teacher::treat;
//    void (Student::*pstArgVoid)() = &Student::eat;
//    connect(m_ptc, ptcArgVoid, m_pst, pstArgVoid);

//    void (Teacher::*ptcWithArg)(QString) = &Teacher::treat;
//    void (Student::*pstWithArg)(QString) = &Student::eat;
//    connect(m_ptc, ptcWithArg, m_pst, pstWithArg);

    //connect(m_ptc, ptcWithArg, m_pst, pstArgVoid);//这个写法是ok的
    //连接信号与槽
    //connect(m_ptc, &Teacher::treat, m_pst, &Student::eat);

    //------C++11的写法解决重载----------
    //在解决信号与槽有重载版本的时候，可以使用C++11的方式
    //QOverload<>::of的方式
//    connect(m_ptc, QOverload<>::of(&Teacher::treat),
//            m_pst, QOverload<>::of(&Student::eat));

//    connect(m_ptc, QOverload<QString>::of(&Teacher::treat),
//            m_pst, QOverload<QString>::of(&Student::eat));

    //------C++14的写法解决重载----------
    //在解决信号与槽有重载版本的时候，可以使用C++14的方式,qOverload<>
//    connect(m_ptc, qOverload<>(&Teacher::treat),
//            m_pst, qOverload<>(&Student::eat));

//    connect(m_ptc, qOverload<QString>(&Teacher::treat),
//            m_pst, qOverload<QString>(&Student::eat));


    //没有信号的接受者的版本
    connect(m_ptc, QOverload<>::of(&Teacher::treat),[]{
        qDebug() << "bbbbb";
    });


    QPushButton *btn = new QPushButton(this);
    btn->setText("点击按钮");
    btn->resize(200, 100);

    connect(btn, &QPushButton::clicked,
            m_ptc, QOverload<>::of(&Teacher::treat));

    //classIsOver();

}

Widget::~Widget()
{
    delete m_ptc;
    delete m_pst;
}

void Widget::classIsOver()
{
    emit m_ptc->treat();
    emit m_ptc->treat("满汉全席");

}

