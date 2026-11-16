#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:
public slots:
    //第一种方式：直接将该函数拷贝的实现文件文件中
    //第二种方式：在函数名字上右键，选择Refactor即可
    //第三种方式：在函数名字上alt + enter
    void eat();
    void eat(QString food);

};

#endif // STUDENT_H
