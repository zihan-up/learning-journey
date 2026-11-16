#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBrush>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *m_timer;
    int m_count = 0;
    int m_hour;
    int m_minute;
    int m_second;
};
#endif // WIDGET_H
