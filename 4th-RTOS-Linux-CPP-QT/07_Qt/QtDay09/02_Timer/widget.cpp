#include "widget.h"
#include "ui_widget.h"

#include <QTimerEvent>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(600, 480);

    //调用startTimer函数，启动定时器
    m_id1 = startTimer(500);

    m_id2 = startTimer(1000);

    //定时器
    QTimer *tm = new QTimer(this);

    connect(tm, &QTimer::timeout, [=]{
        static int num = 1;
        ui->label_3->setText(QString::number(num++));
    });

    tm->start(2000);//启动定时器
}

Widget::~Widget()
{
    delete ui;
}

//重写timerEvent
void Widget::timerEvent(QTimerEvent *ev)
{
    //使用timerId函数获取定时器的标识
    if(m_id1 == ev->timerId())
    {
        static int num1 = 1;
        ui->label->setText(QString::number(num1++));
    }

    if(m_id2 == ev->timerId())
    {
        static int num2 = 1;
        ui->label_2->setText(QString::number(num2++));
    }

}

