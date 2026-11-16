#include "mylabel.h"

#include <QDebug>
#include <QMouseEvent>

MyLabel::MyLabel()
{
    resize(400, 300);

    //第一步：安装事件过滤器
    installEventFilter(this);
}

MyLabel::~MyLabel()
{

}

//鼠标进入
void MyLabel::enterEvent(QEvent *ev)
{
   qDebug() << ">>>鼠标进入范围了";
}

//鼠标离开
void MyLabel::leaveEvent(QEvent *ev)
{
    qDebug() << "鼠标离开范围了<<<";
}

//鼠标移动事件
void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    //因为鼠标进行移动的时候，可能是多个键都被按压了
    //此时如果还使用button是不行的，采用的函数是
    //buttons,也就是几个键的组合方式
    if(ev->buttons() & Qt::LeftButton)
    {
         qDebug() << "鼠标--左键移动--事件触发了";
         qDebug() << "横坐标:" << ev->x()
                  << "纵坐标:" << ev->y();
    }
}

//鼠标按压事件
void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
         qDebug() << "鼠标--左键按压--事件触发了";
         qDebug() << "横坐标:" << ev->x()
                  << "纵坐标:" << ev->y();
    }
}

//鼠标释放事件
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
         qDebug() << "鼠标--左键释放--事件触发了";
         qDebug() << "横坐标:" << ev->x()
                  << "纵坐标:" << ev->y();
    }
}

bool MyLabel::event(QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        qDebug() << "鼠标按压事件被event函数进行了拦截";
        return true;
    }

    return QLabel::event(e);
}

bool MyLabel::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this)
    {
        if(e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *ev = static_cast<QMouseEvent *>(e);
            if(ev->button() == Qt::LeftButton)
            {
                 qDebug() << "鼠标左键按压事件在事件过滤器eventFilter中拦截了";
                 qDebug() << "横坐标:" << ev->x()
                          << "纵坐标:" << ev->y();

                 return true;
            }
        }
    }

    return QLabel::eventFilter(obj, e);
}
