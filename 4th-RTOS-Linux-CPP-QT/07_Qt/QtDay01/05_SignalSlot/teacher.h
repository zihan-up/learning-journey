#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    void treat();//只需要声明，不需要实现
    void treat(QString food);

};

#endif // TEACHER_H
