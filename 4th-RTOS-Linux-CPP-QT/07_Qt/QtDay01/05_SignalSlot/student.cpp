#include "student.h"

#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::eat()
{
    qDebug() << "老师请学生吃大米饭";
}

void Student::eat(QString food)
{
    qDebug() << "老师请学生吃xxxx " << food;
}
