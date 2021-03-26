#include "MediaPushButton.h"
#include <QtMultimedia/QMediaPlayer>

CMediaPushButton::CMediaPushButton(const QString &text,QWidget *parent) :
    QPushButton(text,parent)
{
    init();
}

CMediaPushButton::CMediaPushButton(QWidget *parent) :
    QPushButton(parent)
{
    init();
}

CMediaPushButton::CMediaPushButton(const QString &text) :
    QPushButton(text,0)
{
    init();
}

void CMediaPushButton::enterEvent(QEvent *)
{
    //鼠标进入按钮播放音效->(开始)
    player->setMedia(QUrl(":/voice/PICKUP.WAV"));
    player->setVolume(200);
    player->play();
    //鼠标进入按钮播放音效<-(结束)
}

void CMediaPushButton::leaveEvent(QEvent *)
{
    player->stop();
}

void CMediaPushButton::init()
{
    QPalette pa;
    pa.setColor(QPalette::ButtonText,Qt::white);
    this->setPalette(pa);
    player=new QMediaPlayer(this);
    //cursor=new QCursor(QPixmap(":/new/prefix1/test.png"));
    //setCursor(*cursor);
}
