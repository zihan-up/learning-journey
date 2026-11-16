#include "myapplication.h"

#include <QDebug>

MyApplication::MyApplication(int argc, char **argv)
    :QApplication(argc, argv)
{

}

MyApplication::~MyApplication()
{

}

bool MyApplication::notify(QObject *obj, QEvent *ev)
{
    Q_UNUSED(obj);
    Q_UNUSED(ev);

    qDebug() << "notify拦截所有";

    return true;
}
