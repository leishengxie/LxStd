#include "LsxButton.h"
#include <QPaintEvent>
#include <QPainter>

CLsxButton::CLsxButton(QWidget *parent)
    : QWidget(parent)
    , m_rect(QRect(0, 0, 90, 25))
    , m_bPress(false)
{

}

void CLsxButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if(m_bPress)
    {
        p.setBrush(Qt::darkYellow);        //用画刷来画自己喜欢的颜色
    }
    else
    {
        p.setBrush(Qt::darkGreen);
    }
    p.drawEllipse(m_rect);                    //  有4个参数，分别是位置和长宽，如果长和宽相等就是一个标准的圆了
    p.drawText(m_rect,m_text,QTextOption(Qt::AlignCenter)); //设置文本有三个参数，分别是 对象，文本，文本位置

}

void CLsxButton::mousePressEvent(QMouseEvent *e)
{
    m_bPress = false;

    this->update();             //点击一下更新一下，调用painEvent
}

void CLsxButton::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPress = true;

    this->update();             //点击一下更新一下，调用painEvent
}
