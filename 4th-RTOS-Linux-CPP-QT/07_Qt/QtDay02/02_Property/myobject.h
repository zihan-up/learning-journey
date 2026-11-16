#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
    //显示声明属性（Qt中定义属性的方式）
    Q_PROPERTY(QString name READ getName WRITE setName
               RESET resetName NOTIFY nameChanged)
public:
    explicit MyObject(QObject *parent = nullptr);


    Q_INVOKABLE QString getName() const;
    Q_INVOKABLE void setName(const QString &nme);
    Q_INVOKABLE void resetName();

signals:
    void nameChanged(const QString &nme);
    void func(const QString &nme);
private:
    QString m_name;//数据成员（C++中定义属性的方式）
};

#endif // MYOBJECT_H
