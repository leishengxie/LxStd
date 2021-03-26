#include "LProgressIndicator.h"
#include <QPainter>
#include <QtDebug>

#define SIDE_SIZE   25

CLProgressIndicator::CLProgressIndicator(QWidget* parent)
    : QWidget(parent),
      m_unAngle(0),
      m_nIdTimer(-1),
      m_nDelay(20),
      m_bDisplayedWhenStopped(false),
      m_color(Qt::green)
{
//    大小策略 QSizePolicy
//    Fix  不会发生任何的伸缩
//    minimum  推荐的大小是它的最小尺寸，它不会变得更小，但是可以变得更大
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);

}

bool CLProgressIndicator::isAnimated () const
{
    return (m_nIdTimer != -1);
}

void CLProgressIndicator::setDisplayedWhenStopped(bool state)
{
    m_bDisplayedWhenStopped = state;

    update();
}

bool CLProgressIndicator::isDisplayedWhenStopped() const
{
    return m_bDisplayedWhenStopped;
}


void CLProgressIndicator::startAnimation()
{
    m_unAngle = 0;

    if (m_nIdTimer == -1)
    {
        m_nIdTimer = startTimer(m_nDelay); // timerEvent
    }
}

void CLProgressIndicator::stopAnimation()
{
    if (m_nIdTimer != -1)
    {
        killTimer (m_nIdTimer);
    }

    m_nIdTimer = -1;

    update();
}

void CLProgressIndicator::setAnimationDelay(int delay)
{
    if (m_nIdTimer != -1)
    {
        killTimer(m_nIdTimer);
    }

    m_nDelay = delay;

    if (m_nIdTimer != -1)
    {
        m_nIdTimer = startTimer(m_nDelay);
    }
}

void CLProgressIndicator::setColor(const QColor & color)
{
    m_color = color;

    update();
}

QSize CLProgressIndicator::sizeHint() const
{
    return QSize(SIDE_SIZE, SIDE_SIZE);
}

QRect CLProgressIndicator::rectDraw()
{
    int x = width() / 2 - SIDE_SIZE / 2;
    int y = height() / 2 - SIDE_SIZE / 2;
    return QRect(x, y, SIDE_SIZE, SIDE_SIZE);
}

void CLProgressIndicator::timerEvent(QTimerEvent* /*event*/)
{
    m_unAngle = (m_unAngle + 30) % 360;

    update();
}

void CLProgressIndicator::paintEvent(QPaintEvent* /*event*/)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);    // 抗锯齿

    int width = qMin(rectDraw().width(), height());

    // 外部半径，内部半径
    int outerRadius = (width - 1) >> 1;
    int innerRadius = ((width - 1) >> 1 ) * 0.38;

    // 指针实体高度，宽度，圆角弧度
    int capsuleHeight = outerRadius - innerRadius;
    int capsuleWidth  = (width > 32 ) ? capsuleHeight * .23 : capsuleHeight * .35;
    int capsuleRadius = capsuleWidth >> 1;

    if (m_nProgress > 0 && m_nProgress < 100)
    {
        p.setPen(m_color);
        p.drawText(rectDraw(), Qt::AlignCenter, QString("%1%").arg(m_nProgress));
    }
    else if (m_nProgress == 100)
    {
        stopAnimation();
    }

    ///*******绘图重点*****************************/
    for (int i = 0; i < 12; ++i)
    {
        QColor color = m_color;
        color.setAlphaF(1.0f - (i / 12.0f)); // 设置透明度
        p.setPen(Qt::NoPen);
        p.setBrush(color);
        p.save();
        p.translate(rectDraw().center());   // 平移坐标系，此时点（12.5，12.5）为原点（0，0）
        p.rotate(m_unAngle - i * 30.0f);    // 逆时针旋转 30 度
        p.drawRoundedRect(0, innerRadius, capsuleWidth, capsuleHeight, capsuleRadius, capsuleRadius);
        p.restore();
    }
}


