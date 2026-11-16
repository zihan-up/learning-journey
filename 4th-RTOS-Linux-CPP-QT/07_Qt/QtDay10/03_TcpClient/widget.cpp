#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Tcp Client");
    resize(600, 480);

    //1、使用QTcpSocket创建对象，用于通信
    m_tcpSock = new QTcpSocket(this);

    //2、连接到服务器
    m_tcpSock->connectToHost("127.0.0.1", 8888);

    //3、只要服务器发送数据，那么客户端就会触发readyRead
    connect(m_tcpSock, &QTcpSocket::readyRead, [=]{
        //让客户端读取服务器发送过来的数据
        QByteArray ba = m_tcpSock->readAll();
        ui->listWidget->addItem(QString("客户端接收了服务器的数据：") +
                                QString::fromUtf8(ba));
    });

    //连接断开的时候做的事件
    connect(m_tcpSock, &QTcpSocket::disconnected, [=]{
        m_tcpSock->deleteLater();
        close();
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    //获取QLineEdit中的文本信息
    QString msg = ui->lineEdit->text();

    //将这个文本信息发送给服务器
    m_tcpSock->write(msg.toUtf8());

    ui->listWidget->addItem(QString("客户端向服务器发送数据：")
                            + msg);
    //清空单行文本框中的内容
    ui->lineEdit->clear();
}
