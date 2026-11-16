#include "widget.h"
#include "ui_widget.h"

#include <QTcpSocket>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Tcp Server");
    resize(600, 480);

    //1、创建QTcpServer的对象
    m_tcpServer = new QTcpServer(this);

    //3、连接信号与槽
    connect(m_tcpServer, &QTcpServer::newConnection, this, &Widget::handle);

    //2、监听客户端
    bool ret = m_tcpServer->listen(QHostAddress::Any, 8888);
    if(!ret)
    {
        QMessageBox::critical(this, "critical", "监听失败");
        return;
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handle()
{
    //4、获取到连接
    QTcpSocket *psock = m_tcpServer->nextPendingConnection();

    //5、这个信号readyRead一旦被触发，说明有数据上来
    connect(psock, &QTcpSocket::readyRead, [=]{
        ui->listWidget->addItem("客户端上来了");
        //读取客户端发送过来的数据
        QByteArray ba = psock->readAll();
        ui->listWidget->addItem(QString("服务器接收客户端的数据是: ") +
                                QString::fromUtf8(ba));

        //将相同的数据发送给客户端
        psock->write(ba);
        ui->listWidget->addItem(QString("服务器发送给客户端的数据是: ") +
                                QString::fromUtf8(ba));
    });

    //6、连接断开的时候做的事件
    connect(psock, &QTcpSocket::disconnected, [=]{
        m_tcpServer->close();
        psock->deleteLater();
        close();
    });
}

