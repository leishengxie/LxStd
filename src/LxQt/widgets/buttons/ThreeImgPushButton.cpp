#include "ThreeImgPushButton.h"
#include <QMouseEvent>
#include <QPainter>

CThreeImgPushButton::CThreeImgPushButton(QWidget *parent)
    :QPushButton(parent)
{
    status = NORMAL;
    mouse_press = false;
    resize(QSize(90,25));
    m_strImgNormal = ":/img/btn_style_normal.png";
    m_strImgHover = ":/img/btn_style_normal.png";
    m_strImgPress = ":/img/btn_style_down.png";
}

CThreeImgPushButton::CThreeImgPushButton(const QString text, QWidget *parent)
    : QPushButton(text, parent)
{
    setText(text);
    status = NORMAL;
    mouse_press = false;
    resize(QSize(90,25));
    m_strImgNormal = ":/img/btn_style_normal.png";
    m_strImgHover = ":/img/btn_style_normal.png";
    m_strImgPress = ":/img/btn_style_down.png";
}
CThreeImgPushButton::~CThreeImgPushButton()
{

}


void CThreeImgPushButton::setBgImg(QString strImgNormal, QString strImgHover, QString strImgPress)
{
    m_strImgNormal = strImgNormal;
    m_strImgHover = strImgHover;
    m_strImgPress = strImgPress;
    resize(QPixmap(m_strImgNormal).size());
}

void CThreeImgPushButton::enterEvent(QEvent *)
{
    status = HOVER;
    update();
}
void CThreeImgPushButton::mousePressEvent(QMouseEvent *event)
{
    //若点击鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        status = PRESS;
        update();
    }
}
void CThreeImgPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    //若点击鼠标左键响应
    if(mouse_press&&this->rect().contains(event->pos()))
    {
        mouse_press = false;
        status = HOVER;
        update();
        emit clicked();
    }
}
void CThreeImgPushButton::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}
void CThreeImgPushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    switch(status)
    {
    case NORMAL:
        {
            painter.setPen(QColor(255,255,255));
            pixmap.load(m_strImgNormal);
            break;
        }
    case HOVER:
        {
            painter.setPen(QColor(6,164,166));
            pixmap.load(m_strImgHover);
            break;
        }
    case PRESS:
        {
            pixmap.load(m_strImgPress);
            break;
        }
    default:
        pixmap.load(m_strImgNormal);
    }
    painter.drawPixmap(rect(), pixmap);
    painter.drawText(this->rect(), Qt::AlignCenter, this->text());
}
