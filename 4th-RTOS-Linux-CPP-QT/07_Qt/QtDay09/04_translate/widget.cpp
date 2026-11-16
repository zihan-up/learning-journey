#include "widget.h"

#include <QPainter>
#include <QPen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *ev)
{

#if 0
    //第一种方式：每次保证画家的位置不变，但是在画图形的时候
    //可以指定图形的位置，同时每次画图的时候，画笔的颜色会
    //随着更改
    QPainter pat(this);
    QPen pen;
    pen.setColor(Qt::red);
    pat.setPen(pen);
    pat.drawRect(10, 10, 200, 100);


    pen.setColor(Qt::green);
    pat.setPen(pen);
    pat.drawRect(310, 10, 200, 100);

    pen.setColor(Qt::red);
    pat.setPen(pen);
    pat.drawRect(610, 10, 200, 100);
#endif
#if 0
    //第二种方式：画图的位置不发生任何的更改，但是可以将
    //画家的位置进行更新
    QPainter pat(this);
    QPen pen;
    pen.setColor(Qt::red);
    pat.setPen(pen);
    pat.drawRect(10, 10, 200, 100);

    //移动画家的位置
    pat.translate(300, 0);
    pen.setColor(Qt::green);
    pat.setPen(pen);
    pat.drawRect(10, 10, 200, 100);

    pat.translate(300, 0);
    pen.setColor(Qt::red);
    pat.setPen(pen);
    pat.drawRect(10, 10, 200, 100);
#endif
    //第三种写法：因为第一次与第三次，画图的画笔的颜色是一样的
    //所以可以保存画家的状态
    QPainter pat(this);
    QPen pen;
    pen.setColor(Qt::red);
    pat.setPen(pen);
    pat.drawRect(10, 10, 200, 100);
    pat.save();//保存画家的状态,使用了栈结构，等价于执行push

    //移动画家的位置
    pat.translate(300, 0);
    pen.setColor(Qt::green);
    pat.setPen(pen);
    pat.drawRect(10, 10, 200, 100);
    pat.save();

    pat.restore();//回复状态，使用了栈结构，等价于执行了pop
    pat.restore();//回复状态
    pat.translate(600, 0);

    pat.drawRect(10, 10, 200, 100);
}
