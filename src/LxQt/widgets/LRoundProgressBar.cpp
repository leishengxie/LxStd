﻿#include "LRoundProgressBar.h"
#include "qmath.h"
#include <QPropertyAnimation>
#include <QDebug>

CLRoundProgressBar::CLRoundProgressBar(QWidget* parent) :
    QWidget(parent), _value(0), _min(0), _max(100), _precision(0)
{
    //设置初始角度，顺时针逆时针
    setdefault(90, true);
    //设置默认外圈宽度
    setOutterBarWidth(18);
    //设置默认内圈宽度
    setInnerBarWidth(16);
    //设置默认范围
    setRange(0, 100);
    //设置默认值
    setValue(75);
    //设置外圈颜色
    setOutterColor(QColor(233, 248, 248));
    //设置默认渐变色
    setInnerColor(QColor(49, 177, 190), QColor(133, 243, 244));
    //设置默认文字颜色
    setDefaultTextColor(QColor(49, 177, 190));
    //设置默认精度
    setPrecision(0);
    //设置内圈默认文字样式
    setInnerDefaultTextStyle(CLRoundProgressBar::percent);
}

CLRoundProgressBar::~CLRoundProgressBar()
{
}

//********************************************** 外部接口 ****************************************
//设置初始角度，顺时针逆时针
void CLRoundProgressBar::setdefault(int startAngle, bool clockWise)
{
    _startAngle = startAngle;
    _clockWise = clockWise;
}

//设置外圈宽度
void CLRoundProgressBar::setOutterBarWidth(float width)
{
    _outterBarWidth = width;
}
//设置内圈宽度
void CLRoundProgressBar::setInnerBarWidth(float width)
{
    _innerBarWidth = width;
}

//设置值的范围
void CLRoundProgressBar::setRange(float min, float max)
{
    //todo 和value比较
    if(max < min)
    {
        max = 100;
        min = 0;
    }
    else
    {
        _max = max;
        _min = min;
    }
}

//设置当前值
void CLRoundProgressBar::setValue(float value)
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "_value");
    animation->setDuration(500);
    animation->setStartValue(_value);
    animation->setEndValue(value);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start();
}

void CLRoundProgressBar::_setValue(float value)
{
    _value = value;
    repaint();
}

//设置外圈颜色
void CLRoundProgressBar::setOutterColor(const QColor & outterColor)
{
    _outterColor = outterColor;
}

//设置内圈渐变色
void CLRoundProgressBar::setInnerColor(const QColor & startColor, const QColor & endColor)
{
    _startColor = startColor;
    _endColor = endColor;
}

//设置内圈渐变色
void CLRoundProgressBar::setInnerColor(const QColor & startColor)
{
    _startColor = startColor;
}

void CLRoundProgressBar::setDefaultTextColor(const QColor & textColor)
{
    _textColor = textColor;
}

//设置控制
void CLRoundProgressBar::setControlFlags(int flags)
{
    this->_controlFlags |= flags;
}

//设置显示数字精度
void CLRoundProgressBar::setPrecision(int precision)
{
    _precision = precision;
}

//********************************************** 内部绘制部分 ****************************************
void CLRoundProgressBar::resizeEvent(QResizeEvent* event)
{
    //根据内外圈宽度设置控件最小大小
    if(_outterBarWidth > _innerBarWidth)
    {
        this->setMinimumSize(_outterBarWidth * 8, _outterBarWidth * 8);
    }
    else
    {
        this->setMinimumSize(_innerBarWidth * 8, _innerBarWidth * 8);
    }
    //计算绘制正方形区域信息
    caculateSquare();
}

void CLRoundProgressBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //绘制外圈
    paintOutterBar(painter);
    //绘制内圈
    paintInnerBar(painter);
    //绘制外圈
    paintDot(painter);
    //绘制文字
    paintText(painter);
}

//计算绘制正方形区域信息
void CLRoundProgressBar::caculateSquare()
{
    int minWidth = qMin(this->width(), this->height());
    float barWidth = qMax(_outterBarWidth, _innerBarWidth);
    _squareWidth = minWidth - barWidth - 2;
    _squareStart = barWidth / 2 + 1;
    _dotX = _squareStart + _squareWidth / 2;
    _dotY = _squareStart;
}

//绘制外圈
void CLRoundProgressBar::paintOutterBar(QPainter & painter)
{
    if(!(_controlFlags & outterCirle))
    {
        return;
    }
    QPen pen;
    pen.setWidth(_outterBarWidth);
    pen.setColor(_outterColor);
    painter.setPen(pen);
    QRectF rectangle(_squareStart, _squareStart, _squareWidth, _squareWidth);
    //从90度开始，逆时针旋转
    painter.drawEllipse(rectangle);
}

//绘制内圈
void CLRoundProgressBar::paintInnerBar(QPainter & painter)
{
    QPen pen;
    if(!(_controlFlags & linearColor))
    {
        pen.setColor(_startColor);
    }
    else
    {
        QLinearGradient gradient(0, 0, 0, _squareWidth);
        gradient.setColorAt(0, _startColor);
        gradient.setColorAt(1, _endColor);
        QBrush brush(gradient);
        pen.setBrush(brush);
    }
    pen.setWidth(_innerBarWidth);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    QRectF rectangle(_squareStart, _squareStart, _squareWidth, _squareWidth);
    //从90度开始，逆时针旋转
    int startAngle = _startAngle * 16;
    int spanAngle = (_value - _min) / (_max - _min) * 360 * 16 * (_clockWise ? -1 : 1);
    painter.drawArc(rectangle, startAngle, spanAngle);
}

//绘制装饰圆点
void CLRoundProgressBar::paintDot(QPainter & painter)
{
    if(!(_controlFlags & decorateDot))
    {
        return;
    }
    //当bar宽度小于3时，便不再绘制装饰圆点
    if(_innerBarWidth < 3)
    {
        return;
    }
    painter.setPen(QColor(255, 255, 255));
    painter.setBrush(QColor(255, 255, 255));
    //区域为圆点绘制正方形区域
    painter.drawEllipse(_dotX - _innerBarWidth / 6, _dotY - _innerBarWidth / 6, _innerBarWidth / 3, _innerBarWidth / 3);
}

//绘制默认内置文字
void CLRoundProgressBar::paintText(QPainter & painter)
{
    if(!(_controlFlags & defaultText))
    {
        return;
    }
    painter.setPen(_textColor);
    painter.setFont(QFont("Microsoft YaHei", 22, 75));
    switch (_innerDefaultTextStyle)
    {
        case value:
            painter.drawText(_squareStart, _squareStart, _squareWidth, _squareWidth, Qt::AlignCenter, QString::number(_value, 'f', _precision));
            break;
        case valueAndMax:
            painter.drawText(_squareStart, _squareStart, _squareWidth, _squareWidth, Qt::AlignCenter,
                             QString::number(_value, 'f', _precision) + "/" + QString::number(_max, 'f', _precision));
            break;
        case percent:
            painter.drawText(_squareStart, _squareStart, _squareWidth, _squareWidth, Qt::AlignCenter,
                             QString::number(_value / _max * 100, 'f', _precision) + "%");
            break;
        default:
            break;
    }
}


