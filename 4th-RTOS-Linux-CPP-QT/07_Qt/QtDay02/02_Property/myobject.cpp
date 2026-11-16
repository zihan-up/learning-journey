#include "myobject.h"

MyObject::MyObject(QObject *parent) : QObject(parent)
{

}

QString MyObject::getName() const
{
    return m_name;//此处也可以直接返回"hello",这样可以解决语法问题
}

void MyObject::setName(const QString &nme)
{
    if(m_name != nme)
    {
        m_name = nme;
        emit nameChanged(nme);//触发信号，只要属性值发生变更，就可以触发信号
    }
}

void MyObject::resetName()
{
   m_name = "unsetName";
}
