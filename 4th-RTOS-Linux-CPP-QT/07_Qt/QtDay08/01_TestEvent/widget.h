#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //重写鼠标按压事件
    void mousePressEvent(QMouseEvent *ev) override;
    //重写event函数
    bool event(QEvent *ev) override;

    void keyPressEvent(QKeyEvent *ev) override;
};
#endif // WIDGET_H
