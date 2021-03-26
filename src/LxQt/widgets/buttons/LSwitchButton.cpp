#include "LSwitchButton.h"

#include <QPainter>
#include <QEvent>
#include <QTimer>
#include <QtDebug>

static const int s_nWidthThis = 80;
static const int s_nHeightThis = 28;

CLSwitchButton::CLSwitchButton(QWidget* parent)
    : QWidget(parent)
{
    m_bChecked = false;
    m_eButtonStyle = EBS_Rect;

    bgColorOff = QColor(225, 225, 225);
    bgColorOn = QColor(250, 250, 250);

    sliderColorOff = QColor(100, 100, 100);
    sliderColorOn = QColor(100, 184, 255);

    textColorOff = QColor(255, 255, 255);
    textColorOn = QColor(10, 10, 10);

    m_strTextOff = "关";
    m_strTextOn = "开";

    imageOff = ":/image/btncheckoff1.png";
    imageOn = ":/image/btncheckon1.png";

    space = 2;
    rectRadius = 5;

    step = width() / 50;
    startX = 0;
    endX = 0;

    timer = new QTimer(this);
    timer->setInterval(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Microsoft Yahei", 10));
}

CLSwitchButton::~CLSwitchButton()
{

}

void CLSwitchButton::mousePressEvent(QMouseEvent*)
{
    m_bChecked = !m_bChecked;
    emit checkedChanged(m_bChecked);

    //每次移动的步长为宽度的 50分之一
    step = width() / 50;

    //状态切换改变后自动计算终点坐标
    if (m_bChecked)
    {
        if (m_eButtonStyle == EBS_Rect)
        {
            endX = width() - width() / 2;
        }
        else if (m_eButtonStyle == EBS_CircleIn)
        {
            endX = width() - height();
        }
        else if (m_eButtonStyle == EBS_CircleOut)
        {
            endX = width() - height() + space;
        }
    }
    else
    {
        endX = 0;
    }

    timer->start();
}

void CLSwitchButton::resizeEvent(QResizeEvent*)
{
    //每次移动的步长为宽度的 50分之一
    step = width() / 50;

    //尺寸大小改变后自动设置起点坐标为终点
    if (m_bChecked)
    {
        if (m_eButtonStyle == EBS_Rect)
        {
            startX = width() - width() / 2;
        }
        else if (m_eButtonStyle == EBS_CircleIn)
        {
            startX = width() - height();
        }
        else if (m_eButtonStyle == EBS_CircleOut)
        {
            startX = width() - height() + space;
        }
    }
    else
    {
        startX = 0;
    }

    update();
}

void CLSwitchButton::paintEvent(QPaintEvent*)
{

    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_eButtonStyle == EBS_Image)
    {
        //绘制图片
        drawImage(&painter);
    }
    else
    {
        //绘制背景
        drawBg(&painter);
        //绘制滑块
        drawSlider(&painter);
        //绘制文字
        drawText(&painter);
    }
}

void CLSwitchButton::drawBg(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!m_bChecked)
    {
        painter->setBrush(bgColorOff);
    }
    else
    {
        painter->setBrush(bgColorOn);
    }

    if (m_eButtonStyle == EBS_Rect)
    {
        painter->drawRoundedRect(rect(), rectRadius, rectRadius);
    }
    else if (m_eButtonStyle == EBS_CircleIn)
    {
        QRect rect(0, 0, width(), height());
        //半径为高度的一半
        int radius = rect.height() / 2;
        //圆的宽度为高度
        int circleWidth = rect.height();

        QPainterPath path;
        path.moveTo(radius, rect.left());
        path.arcTo(QRectF(rect.left(), rect.top(), circleWidth, circleWidth), 90, 180);
        path.lineTo(rect.width() - radius, rect.height());
        path.arcTo(QRectF(rect.width() - rect.height(), rect.top(), circleWidth, circleWidth), 270, 180);
        path.lineTo(radius, rect.top());

        painter->drawPath(path);
    }
    else if (m_eButtonStyle == EBS_CircleOut)
    {
        QRect rect(space, space, width() - space * 2, height() - space * 2);
        painter->drawRoundedRect(rect, rectRadius, rectRadius);
    }

    painter->restore();
}

void CLSwitchButton::drawSlider(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!m_bChecked)
    {
        painter->setBrush(sliderColorOff);
    }
    else
    {
        painter->setBrush(sliderColorOn);
    }

    if (m_eButtonStyle == EBS_Rect)
    {
        int sliderWidth = width() / 2 - space * 2;
        int sliderHeight = height() - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth, sliderHeight);
        painter->drawRoundedRect(sliderRect, rectRadius, rectRadius);
    }
    else if (m_eButtonStyle == EBS_CircleIn)
    {
        QRect rect(0, 0, width(), height());
        int sliderWidth = rect.height() - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
    }
    else if (m_eButtonStyle == EBS_CircleOut)
    {
        QRect rect(0, 0, width() - space, height() - space);
        int sliderWidth = rect.height();
        QRect sliderRect(startX, space / 2, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
    }

    painter->restore();
}

void CLSwitchButton::drawText(QPainter* painter)
{
    painter->save();

    if (!m_bChecked)
    {
        if (m_eButtonStyle == EBS_Rect)
        {
        painter->setPen(textColorOff);
        painter->drawText(width() / 2, 0, width() / 2 - space, height(), Qt::AlignCenter, m_strTextOff);
        }
        else
        {
            painter->setPen(textColorOff);
            painter->drawText(height(), 0, width() - height(), height(), Qt::AlignCenter, m_strTextOff);
        }
    }
    else
    {
        if (m_eButtonStyle == EBS_Rect)
        {
        painter->setPen(textColorOn);
        painter->drawText(0, 0, width() / 2 + space * 2, height(), Qt::AlignCenter, m_strTextOn);
        }
        else
        {
            painter->setPen(textColorOn);
            painter->drawText(0, 0, width() - height(), height(), Qt::AlignCenter, m_strTextOn);
        }
    }

    painter->restore();
}

void CLSwitchButton::drawImage(QPainter* painter)
{
    painter->save();

    QPixmap pix;

    if (!m_bChecked)
    {
        pix = QPixmap(imageOff);
    }
    else
    {
        pix = QPixmap(imageOn);
    }

    //自动等比例平滑缩放居中显示
    int targetWidth = pix.width();
    int targetHeight = pix.height();
    pix = pix.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    int pixX = rect().center().x() - targetWidth / 2;
    int pixY = rect().center().y() - targetHeight / 2;
    QPoint point(pixX, pixY);
    painter->drawPixmap(point, pix);

    painter->restore();
}

QSize CLSwitchButton::sizeHint() const
{
    // 注意const 函数
    const QFontMetrics fontMetrics = this->fontMetrics();
    int nWidthTextOn = fontMetrics.width(getTextOn());
    int nWidthTextOff = fontMetrics.width(getTextOff());

    int nWidthTextLarger = qMax(nWidthTextOn, nWidthTextOff);;
    int nWidthThis = height() + nWidthTextLarger;
    int nWidthThisLarger = qMax(nWidthThis, s_nWidthThis);

    return QSize(nWidthThisLarger, s_nHeightThis);
}

void CLSwitchButton::updateValue()
{
    if (m_bChecked)
    {
        if (startX < endX)
        {
            startX = startX + step;
        }
        else
        {
            startX = endX;
            timer->stop();
        }
    }
    else
    {
        if (startX > endX)
        {
            startX = startX - step;
        }
        else
        {
            startX = endX;
            timer->stop();
        }
    }

    update();
}



void CLSwitchButton::setChecked(bool bChecked)
{
    if (this->m_bChecked != bChecked)
    {
        this->m_bChecked = bChecked;
        emit checkedChanged(bChecked);
        update();
    }
}

void CLSwitchButton::setButtonStyle(CLSwitchButton::E_ButtonStyle eButtonStyle)
{
    this->m_eButtonStyle = eButtonStyle;
    update();
}

void CLSwitchButton::setBgColor(QColor bgColorOff, QColor bgColorOn)
{
    this->bgColorOff = bgColorOff;
    this->bgColorOn = bgColorOn;
    update();
}

void CLSwitchButton::setSliderColor(QColor sliderColorOff, QColor sliderColorOn)
{
    this->sliderColorOff = sliderColorOff;
    this->sliderColorOn = sliderColorOn;
    update();
}

void CLSwitchButton::setTextColor(QColor textColorOff, QColor textColorOn)
{
    this->textColorOff = textColorOff;
    this->textColorOn = textColorOn;
    update();
}



void CLSwitchButton::setImage(QString imageOff, QString imageOn)
{
    this->imageOff = imageOff;
    this->imageOn = imageOn;
    update();
}

void CLSwitchButton::setSpace(int space)
{
    this->space = space;
    update();
}

void CLSwitchButton::setRectRadius(int rectRadius)
{
    this->rectRadius = rectRadius;
    update();
}

