#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel();
    ~MyLabel();

    //鼠标进入
    void enterEvent(QEvent *ev) override;
    //鼠标离开
    void leaveEvent(QEvent *ev) override;
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *ev) override;
    //鼠标按压事件
    void mousePressEvent(QMouseEvent *ev) override;
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *ev) override;
};

#endif // MYLABEL_H
