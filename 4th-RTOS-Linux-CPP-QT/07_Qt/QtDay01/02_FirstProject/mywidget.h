#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    //Q_OBJECT是Qt的内置宏,使用该宏的目的是为了
    //后续可以使用Qt自己的语法，特别的，使用了该宏
    //之后，就可以使用元对象系统
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
};
#endif // MYWIDGET_H
