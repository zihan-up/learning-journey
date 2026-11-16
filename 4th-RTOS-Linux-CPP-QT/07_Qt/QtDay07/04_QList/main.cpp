#include <QCoreApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QString> lst;
    lst << "北京" << "上海" << "深圳" << "天津" << "重庆";

    //遍历,使用的是STL格式
    for(QList<QString>::const_iterator it = lst.constBegin();
        it != lst.constEnd(); ++it)
    {
        qDebug() << *it;
    }

    //Java风格
    qDebug() << endl << endl << "Java风格的遍历方式";
    QListIterator<QString> lstIt(lst);
    while(lstIt.hasNext())
    {
        qDebug() << lstIt.next();
    }

    return a.exec();
}
