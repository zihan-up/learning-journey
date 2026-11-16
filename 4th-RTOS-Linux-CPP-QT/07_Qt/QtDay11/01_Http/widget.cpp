#include "widget.h"
#include "ui_widget.h"


#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(1000, 800);

    m_manager = new QNetworkAccessManager(this);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString msg = ui->lineEdit->text();

    QUrl url(msg);
    QNetworkRequest res(url);

    QNetworkReply *reply = m_manager->get(res);

    connect(reply, &QNetworkReply::finished, [=]{
        //读取的结果是正常的
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray ba = reply->readAll();
            ui->plainTextEdit->setPlainText(QString::fromUtf8(ba));
        }
        else
        {
            QString msg = reply->errorString();
            ui->plainTextEdit->setPlainText(msg);
        }
    });
}
