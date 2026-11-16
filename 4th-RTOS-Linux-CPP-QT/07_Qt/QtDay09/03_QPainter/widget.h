#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //重写paintEvent函数
    void paintEvent(QPaintEvent *ev) override;
};
#endif // WIDGET_H
