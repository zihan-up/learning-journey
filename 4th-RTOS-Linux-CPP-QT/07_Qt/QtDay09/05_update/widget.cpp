#include "widget.h"

#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_pos(0)
{
    resize(1000, 800);

    QTimer *tm = new QTimer(this);

    connect(tm, &QTimer::timeout, [=]{
        //paintEvent(nullptr);//error,不能使用绘图引擎
        //repaint();
        update();
    });

    tm->start(100);
}

Widget::~Widget()
{
}

//想在QWidget的对象或者子对象上画一个图片，每隔0.1秒的时间
//将图片向右移动10个单位(将横坐标每0.1s增加10个单位)
void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter pat(this);

//    static int pos = 0;
//    pat.drawPixmap(pos, 0, QPixmap(":/wangdao.png"));
//    pos += 10;

    if(m_pos > this->width())
    {
        m_pos = 0;
    }

    pat.drawPixmap(m_pos, 0, QPixmap(":/wangdao.png"));
    m_pos += 10;
}

