#include "LHoverLabel.h"
#include <QEvent>
#include <QPainter>

CLHoverLabel::CLHoverLabel(QWidget *parent)
    :QLabel(parent)
    ,m_bEnter(false)
{

}

CLHoverLabel::CLHoverLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel(text, parent, f)
    ,m_bEnter(false)
{

}

void CLHoverLabel::enterEvent(QEvent *event)
{
    if(event->type() == QEvent::Enter)
    {
        m_bEnter = true;
        update();
    }
}

void CLHoverLabel::leaveEvent(QEvent *event)
{
    if(event->type() == QEvent::Leave)
    {
        m_bEnter = false;
        update();
    }
}

void CLHoverLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (m_bEnter)
    {
        painter.setPen(QPen(Qt::red));
    }
    else
    {
        painter.setPen(QPen(Qt::blue));
    }
    painter.drawRect(QRect(0,0,this->width()-1,this->height()-1));
}
