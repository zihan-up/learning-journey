#include "widget.h"

#include <QPushButton>
#include <QMediaPlayer>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QPushButton *btn = new QPushButton("点击选择对应的文件", this);
    btn->move(100, 100);
    btn->resize(200, 50);

    //创建多媒体的对象
    QMediaPlayer *mp = new QMediaPlayer(this);

    connect(btn, &QPushButton::clicked, [=]{
        QString path =
                QFileDialog::getOpenFileName(this, "capation"
                                             , "C:/Users/lili/Desktop/嵌入式4期/2Qt课件/mp3文件"
                                             , "(*.mp3);;(*.mp4)");
        //指定要播放的音频文件
        mp->setMedia(QMediaContent(path));

        //播放音频
        mp->play();
    });
}

Widget::~Widget()
{
}

