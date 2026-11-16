#include "HttpTestWidget.h"
#include "ui_HttpTestWidget.h"
#include "CryptString.h"
#include "nlohmann/json.hpp"

#include <QNetworkReply>
#include <QUrlQuery>
#include <QThread>

#include <map>
#include <iostream>

HttpTestWidget::HttpTestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HttpTestWidget)
    , _httpClient(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    setWindowTitle("HTTP客户端");
}

HttpTestWidget::~HttpTestWidget()
{
    delete ui;
}

void HttpTestWidget::on_sendButton_clicked()
{
    //recordListRequest();
    //channelConfigRequest();
    ptzControlRequest("l");
    QThread::sleep(1);
    ptzControlRequest("s");
}

void HttpTestWidget::recordListRequest()
{
    KVQuery kvs;
    kvs.add("start_time", "1673193600000");
    kvs.add("end_time", "1673279999999");
    kvs.add("channel", "0");

    QString tmp = QString::fromStdString(kvs.toString());
    qDebug() << "before crypt tmp:" << tmp << endl;
    // ------------------------------------------------
    CryptString cryptStr(tmp);
    QString token = cryptStr.generateMD5();
    qDebug() << "token:" << token << endl;
    kvs.add("token", token.toStdString());
    kvs.erase("secret");//去掉secret

    //重新生成query
    tmp = QString::fromStdString(kvs.toString());
    qDebug() << "query:" << tmp << endl;
    // ------------------------------------------------
    QUrl url("http://192.168.105.222/xsw/api/reord/list");
    url.setQuery(tmp);
    qDebug() << "url:" << url.toString() << endl;

    doRequest(url);
}

void HttpTestWidget::channelConfigRequest()
{
#if 0
    KVQuery kvs;
    QString tmp = QString::fromStdString(kvs.toString());
    qDebug() << "before crypt tmp:" << tmp << endl;
    // ------------------------------------------------
    CryptString cryptStr(tmp);
    QString token = cryptStr.generateMD5();
    qDebug() << "token:" << token << endl;
    kvs.add("token", token.toStdString());
    kvs.erase("secret");//去掉secret
    tmp = QString::fromStdString(kvs.toString());
    qDebug() << "after crypt query:" << tmp << endl;
#endif
    KVQuery kvs;
    // ------------------------------------------------
    QUrl url("http://192.168.105.222/xsw/getConfig");
    url.setQuery(QString::fromStdString(kvs.toCrpytString()));
    qDebug() << "url:" << url.toString() << endl;
    doRequest(url);
}

void HttpTestWidget::ptzControlRequest(const string & direction)
{
    KVQuery kvs;
    kvs.add("value", direction);
    kvs.add("channelId", "1");
    kvs.add("speed", "69");

    QUrl url("http://192.168.105.222/xsw/api/ptz/control");
    url.setQuery(QString::fromStdString(kvs.toCrpytString()));
    qDebug() << "url:" << url.toString() << endl;

    doRequest(url);
}

void HttpTestWidget::doRequest(const QUrl &url)
{
    QNetworkRequest request(url);

    QNetworkReply * response = _httpClient->get(request);

    connect(response, &QNetworkReply::finished, [=](){
        if(response->error() == QNetworkReply::NoError) {
            //响应成功时
            QString msg(response->readAll());
            ui->respnseText->setText(msg);
            qDebug() << "msg:" << msg << endl;
            QByteArray arr = msg.toUtf8();
            string stdmsg = arr.toStdString();
            std::cout << "stdmsg:" << stdmsg << std::endl;
#if 0
            //解析字段
            using Json = nlohmann::json;
            Json j(stdmsg);
            stdmsg = j.dump(4);
            std::cout << "stdmsg2:" << stdmsg << std::endl;
            std::cout << j["code"] << std::endl;

            Json encode = j[std::string("encode")];
            stdmsg = encode.dump(4);
            std::cout << "stdmsg:" << stdmsg << std::endl;
            //Json channel = j["encode"][0]["valid_ch"];
            //int cnt = channel["valid_ch"];
            //qDebug() << "cnt:" << cnt;
#endif

        } else {
            //响应出错
            QString errorMsg(response->errorString());
            qDebug() << "error:" << errorMsg << endl;
            ui->respnseText->setText(errorMsg);
        }
        response->deleteLater();
    });
}



