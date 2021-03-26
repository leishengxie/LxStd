#include "TextMovingWidget.h"

#include <QTimer>
#include <QPainter>

const int WIDGET_DEFUALT_WIDTH = 100;
const int MARGIN_LEFT_RIGHT_EDGE = 5;

CLTextMovingWidget::CLTextMovingWidget(const QString str, E_MoveType eMoveType, QWidget* parent)
    : QWidget(parent)
    , m_strText(str)
    , m_eMoveType(eMoveType)
    , m_nX(0)
    , m_bTittleTextNeedMove(true)
{
    if (textWidth() > width())
    {
        m_eMoveDirectionCur = EM_RightToLeft;
        m_eMoveDirectionPre = EM_RightToLeft;
    }
    else
    {
        if (EM_HorseRaceLamp == m_eMoveType)
        {
            m_eMoveDirectionCur = EM_RightToLeft;
            m_eMoveDirectionPre = EM_RightToLeft;
        }
        else
        {
            m_eMoveDirectionCur = EM_LeftToRight;
            m_eMoveDirectionPre = EM_LeftToRight;
        }
    }
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(slot_updateTextGeometry()));
    m_pTimer->setInterval(30);
    m_pTimer->start();

}

CLTextMovingWidget::~CLTextMovingWidget()
{

}

void CLTextMovingWidget::setText(const QString & strText)
{
    m_strText = strText;
}

void CLTextMovingWidget::setMoveType(CLTextMovingWidget::E_MoveType eMoveType)
{
    m_eMoveType = eMoveType;
}

void CLTextMovingWidget::setTittleTextNeedMove(bool bNeed)
{
    m_bTittleTextNeedMove = bNeed;
}

int CLTextMovingWidget::textWidth() const
{
    QFontMetrics metrics(font());
    return metrics.width(m_strText);
}

void CLTextMovingWidget::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    QFontMetrics metric(font());
    int y = ( height() - metric.height() ) / 2;
    p.drawText(m_nX, y, metric.width(m_strText), metric.height(), Qt::AlignLeft, m_strText);
}

void CLTextMovingWidget::updateMoveDirection()
{
    // 跑马灯不需要改变移动方向
    if (m_eMoveType == EM_HorseRaceLamp)
    {
        return;
    }

    int nTextWidth = textWidth();
    if(nTextWidth <= width())
    {
        // 移动到最左侧改变方向
        if(m_nX <= 0)
        {
            m_eMoveDirectionCur = EM_LeftToRight;
        }
        else if(m_nX + nTextWidth > width())
        {
            m_eMoveDirectionCur = EM_RightToLeft;
        }

    }
    else
    {
        if(m_nX <= width() - nTextWidth)
        {
            m_eMoveDirectionCur = EM_LeftToRight;
        }
        else if(m_nX > 0)
        {
            m_eMoveDirectionCur = EM_RightToLeft;
        }
    }
    if (m_eMoveDirectionCur != m_eMoveDirectionPre)
    {
        emit sigMoveDirectionChanged();
        m_eMoveDirectionPre = m_eMoveDirectionCur;
    }
}

void CLTextMovingWidget::slot_updateTextGeometry()
{
    updateMoveDirection();
    if (m_eMoveType == EM_HorseRaceLamp)
    {
        if (m_nX < -textWidth())
        {
            m_nX = width();
        }
        m_nX--;
    }
    else
    {
        (m_eMoveDirectionCur == EM_LeftToRight) ? m_nX++ : m_nX--;
    }
    update();
}
