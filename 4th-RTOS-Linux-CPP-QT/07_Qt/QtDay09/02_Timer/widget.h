#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //重写timerEvent函数
    void timerEvent(QTimerEvent *ev) override;

private:
    Ui::Widget *ui;
    int m_id1;
    int m_id2;
};
#endif // WIDGET_H
