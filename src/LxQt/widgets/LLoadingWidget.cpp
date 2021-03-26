#include "LLoadingWidget.h"
#include "qmath.h"
#include <QDebug>

// 默认点的属性
#define DEFAULT_DOT_COLOR           QColor(49, 177, 190)        // 默认点的颜色
#define DEFAULT_DOT_MIN_DIAMETER    5                           // 默认点的最小直径
#define DEFAULT_DOT_MAX_DIAMETER    30                          // 默认点的最大直径

#define DEFAULT_DOTS_COUNT          20                          // 默认点的个数
#define DEFAULT_SIDE_SIZE           200                          // 本widget边长

CLLoadingWidget::CLLoadingWidget(QWidget *parent)
    : QWidget(parent)
    ,m_Interval(50)
    ,m_nIndex(0)
    , m_colorDot(DEFAULT_DOT_COLOR)
    , m_nCountDot(DEFAULT_DOTS_COUNT)
    , m_fMaxDiameterDot(DEFAULT_DOT_MAX_DIAMETER)
    , m_fMinDiameterDot(DEFAULT_DOT_MIN_DIAMETER)
{
    //设置背景透明
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);

    connect(&m_timer,&QTimer::timeout,this,&CLLoadingWidget::refresh);

}

//********************************************** 设置部分 *************************************
//设置点的个数
void CLLoadingWidget::setDotCount(int count)
{
    m_nCountDot=count;
}

//设置点的颜色
void CLLoadingWidget::setDotColor(const QColor & color)
{
    m_colorDot=color;
}

//开始动画
void CLLoadingWidget::start()
{
    m_timer.setInterval(m_Interval);
    m_timer.start();
}

//设置最大直径
void CLLoadingWidget::setMaxDiameter(float max)
{
    m_fMaxDiameterDot=max;
}

//设置最小直径
void CLLoadingWidget::setMinDiameter(float min)
{
    m_fMinDiameterDot=min;
}

QSize CLLoadingWidget::sizeHint() const
{
    return QSize(DEFAULT_SIDE_SIZE, DEFAULT_SIDE_SIZE);
}

//********************************************** 绘制部分 *************************************
//刷新界面
void CLLoadingWidget::refresh()
{
    repaint();
}

void CLLoadingWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    caculate();
}

void CLLoadingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(m_colorDot);
    painter.setBrush(m_colorDot);

    //绘制点
    paintDot(painter);
}

//计算绘制正方形区域
void CLLoadingWidget::caculate()
{
    m_fSideWidth = qMin(width(), height());
    float half = m_fSideWidth / 2;
    m_fCenterDistance = half - m_fMaxDiameterDot / 2 - 1;

    // 相邻点半径差
    float radiiGap = (m_fMaxDiameterDot - m_fMinDiameterDot) / (m_nCountDot - 1) / 2;
    // 点之间的平均角度
    float angleGap = (float)360 / m_nCountDot;

    m_listLocation.clear();
    m_listRadii.clear();

    for(int i = 0; i < m_nCountDot; i++)
    {
        m_listRadii.append(m_fMaxDiameterDot / 2 - i * radiiGap);
        // 角度转换成弧度值
        float radian = qDegreesToRadians(-angleGap * i);

        m_listLocation.append(Location( half + m_fCenterDistance * qCos(radian), half - m_fCenterDistance * qSin(radian)));
    }
}

//绘制圆点
void CLLoadingWidget::paintDot(QPainter& painter)
{
    for(int i=0; i < m_nCountDot; i++)
    {
        painter.setPen(m_colorDot);
        //半径
        float radii = m_listRadii.at((m_nIndex + m_nCountDot - i) % m_nCountDot);

        //绘制圆点
        painter.drawEllipse(QPointF(m_listLocation.at(i).x, m_listLocation.at(i).y), radii, radii);
        //绘制正方形
        //painter.drawRect(locationList.at(i).x,locationList.at(i).y,radii,radii);
        //绘制文字
        //QFont font("Microsoft YaHei",radii*1.2,75);
        //painter.setFont(font);
        //painter.drawText(QPointF(locationList.at(i).x,locationList.at(i).y),u8"霞");
    }
    m_nIndex++;
}
