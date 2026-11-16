#ifndef HTTPTESTWIDGET_H
#define HTTPTESTWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <string>
using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class HttpTestWidget; }
QT_END_NAMESPACE

class HttpTestWidget : public QWidget
{
    Q_OBJECT

public:
    HttpTestWidget(QWidget *parent = nullptr);
    ~HttpTestWidget();

    void recordListRequest();
    void channelConfigRequest();
    void ptzControlRequest(const string & direction);

    void doRequest(const QUrl & url);

private slots:
    void on_sendButton_clicked();

private:
    Ui::HttpTestWidget *ui;

    QNetworkAccessManager * _httpClient;
};
#endif // HTTPTESTWIDGET_H
