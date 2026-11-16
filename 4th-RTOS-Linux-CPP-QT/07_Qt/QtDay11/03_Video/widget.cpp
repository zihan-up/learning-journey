#include "widget.h"

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    QPushButton *btn = new QPushButton("点击选择视频文件");
    QVideoWidget *videoWid = new QVideoWidget;

    QMediaPlayer *mp = new QMediaPlayer(this);
    mp->setVideoOutput(videoWid);

    connect(btn, &QPushButton::clicked, [=]{
        QString path =
                QFileDialog::getOpenFileName(this, "caption"
                                            , "F:/ev录屏"
                                            , "(*.mp4)");
        mp->setMedia(QMediaContent(path));

        mp->play();

    });

    QVBoxLayout *vlayout = new QVBoxLayout;

    vlayout->addWidget(videoWid);
    vlayout->addWidget(btn);

    setLayout(vlayout);
}

Widget::~Widget()
{
}

