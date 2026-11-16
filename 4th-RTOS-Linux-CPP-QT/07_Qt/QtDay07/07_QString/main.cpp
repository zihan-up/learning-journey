#include <QCoreApplication>

#include <QDebug>
#include <iostream>

using namespace std;

void test()
{
    QString s1("hello");
    QString s2 = s1;

    qDebug() << "s1 = " << s1 ;
    qDebug() << "s2 = " << s2 ;
    qDebug() << "s1.constData() = " << s1.constData();
    qDebug() << "s2.constData() = " << s2.constData();

    qDebug() << Qt::endl << Qt::endl;
    s1[0] = 'H';
    qDebug() << "s1 = " << s1 ;
    qDebug() << "s2 = " << s2 ;
    qDebug() << "s1.constData() = " << s1.constData();
    qDebug() << "s2.constData() = " << s2.constData();

    //格式化操作的
    qDebug() << QString("这是一个字符串 %2  %1").arg(10).arg("hello");
}

void test2()
{
    //QByteArray的对象
    QByteArray ba("hello");
    qDebug() <<"ba = " << ba;

    //从QByteArray的对象转换到QString类型
    QString s1(ba);
    qDebug() << "QString s1 = " << s1;

    QString s3;
    s3 = QString::fromUtf8(ba);
    qDebug() << "QString s3 = " << s3;

    //从QString类型转换到QByteArray的类型
    QString s2("wangdao");
    ba = s2.toUtf8();
    qDebug() << "QByteArray ba = " << ba;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QString s1("wangdao");
    qDebug() << "s1 = " << s1;
    qDebug().noquote().nospace() << "s1 =" << s1;

    qDebug() << "s1 = " << s1.toUtf8().constData();

    return a.exec();
}
