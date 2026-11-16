#include "myobject.h"

#include <QDebug>

MyObject::MyObject(QObject *parent)
    : QObject(parent)
{
    qDebug() << "MyObject(QObject *)";
}

MyObject::~MyObject()
{
    qDebug() << "~MyObject()";
}
