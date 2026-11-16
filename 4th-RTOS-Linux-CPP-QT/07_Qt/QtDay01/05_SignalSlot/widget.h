#ifndef WIDGET_H
#define WIDGET_H

#include "teacher.h"
#include "student.h"
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void classIsOver();
private:
    Teacher *m_ptc;
    Student *m_pst;
};
#endif // WIDGET_H
