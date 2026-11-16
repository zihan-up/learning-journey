#include "widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
: QWidget(parent)
{
    //创建定时器对象
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, [&](){
        m_count++;
        update();
    });

    m_timer->start(1000);

    //这句话的含义是：获取当前时间，比如："19:20:58 下午",那么
    //t = QString("19:20:58 下午");
    //list1会将t以空格为分隔符，分为("19:20:58", "下午")
    //list2会将list1[0],也就是QString("19:20:58"),分为("19","20","58")
    //然后m_hour = 19,m_minute = 20,m_second = 58
    QString t = QTime::currentTime().toString("h:m:s ap");
    QStringList list1 = t.split(" ");
    QStringList list2 = list1[0].split(":");
    m_hour = list2[0].toUInt();
    m_minute = list2[1].toUInt();
    m_second = list2[2].toUInt();

    //此处使用打印可以得出结果
    qDebug() << "t = " << t
             << "list1 = " << list1
             << "list2 = " << list2
             << "m_hour = " << m_hour
             << "m_minute = " << m_minute
             << "m_second = " << m_second;
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    //绘制圆
    QPainter pat(this);

    QPen pen(QColor("skyblue"));
    pen.setWidth(3);
    QBrush b("pink");
    pat.setPen(pen);
    pat.setBrush(b);

    //移动画家的位置，然后画圆
    pat.translate(this->width()/2, this->height()/2);
    pat.drawEllipse(QPoint(0, 0), 200, 200);

    //绘制刻度
    pen.setColor(QColor("black"));
    pat.setPen(pen);
    for (int i = 0; i < 60; ++i)
    {
        pat.rotate(6);
        pat.drawLine(QPoint(200, 0), QPoint(195, 0));
    }

    pen.setWidth(5);
    pat.setPen(pen);
    for(int i = 0; i < 12; ++i)
    {
        pat.rotate(30);
        pat.drawLine(QPoint(200, 0),QPoint(190, 0));
        pat.drawText(QPoint(-5, -165), QString("%1").arg(i + 1));
    }

    //制作时针
    pen.setWidth(6);
    pen.setColor("blue");
    pat.setPen(pen);
    pat.rotate(m_hour * 30 + 6 * m_second/60/12
             + 30 * m_minute/60 + 6 * m_count/60/12);
    pat.drawLine(QPoint(0, -50), QPoint(0, 5));

    //制作分针
    QPainter patMinute(this);
    patMinute.translate(this->width()/2, this->height()/2);
    pen.setWidth(6);
    pen.setColor("green");
    patMinute.setPen(pen);
    patMinute.rotate(6 * m_count/60 + 6 * m_minute + 6 * m_second/60);
    patMinute.drawLine(QPoint(0, -100), QPoint(0, 2));

    //制作秒针
    QPainter patSecond(this);
    patSecond.translate(this->width()/2, this->height()/2);
    pen.setWidth(6);
    pen.setColor("black");
    patSecond.setPen(pen);
    patSecond.rotate(6 * m_count + 6 * m_second);
    patSecond.drawLine(QPoint(0, -100), QPoint(0, 2));
}
