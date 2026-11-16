#include "widget.h"

#include <QTimeEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QCalendarWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    QTimeEdit *tmedit = new QTimeEdit(QTime::currentTime(), this);
    tmedit->move(100, 0);
    tmedit->resize(300, 30);

    QDateEdit *dtEdit = new QDateEdit(QDate::currentDate(), this);
    dtEdit->move(100, 100);
    dtEdit->resize(300, 30);

    QDateTimeEdit *datetmEdit =
            new QDateTimeEdit(QDateTime::currentDateTime(), this);
    datetmEdit->move(100, 200);
    datetmEdit->resize(300, 30);

    QCalendarWidget *cw = new QCalendarWidget(this);
    cw->move(100, 300);
    cw->resize(400, 400);
}

Widget::~Widget()
{
}

