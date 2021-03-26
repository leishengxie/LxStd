#include "LSliderButtons.h"

#define ITEM_SPACE 15           // 项之间的间隔
#define PYSB_RECT_RADIUS 8      // 项和widget的弧度值
#define PYSB_HEIGHT 30          // 默认widget高度

#define COLOR_BG_START QColor(121,121,121)
#define COLOR_BG_END   QColor(78,78,78)

#define PYSB_BAR_WIDTH_INCREMENT 2
#define PYSB_BAR_SLIDE_INCREMENT 3

#define PYSB_SLIDE_TIMER_INTERVAL 20
#define PYSB_SHRINK_TIMER_INTERVAL 20

#define PYSB_BAR_SKIN1

#ifdef PYSB_BAR_SKIN1
#define PYSB_BAR_START_COLOR QColor(46,132,243)
#define PYSB_BAR_END_COLOR QColor(39,110,203)
#endif

#ifdef PYSB_BAR_SKIN2
#define PYSB_BAR_START_COLOR QColor(255,177,42)
#define PYSB_BAR_END_COLOR QColor(225,156,37)
#endif

#ifdef PYSB_BAR_SKIN3
#define PYSB_BAR_START_COLOR QColor(148,255,82)
#define PYSB_BAR_END_COLOR QColor(133,229,73)
#endif

CLSliderButtons::CLSliderButtons(QWidget *parent) :
    QWidget(parent)
{
    m_colorItemPoint0=QColor::fromRgb(46,132,243);
    m_colorItemPoint1=QColor::fromRgb(39,110,203);

    m_bForward = true;
    m_bShrink = false;
    m_bVirgin = true;

    m_timerSlide = new QTimer(this);
    m_timerSlide->setInterval(PYSB_SLIDE_TIMER_INTERVAL);
    connect(m_timerSlide,SIGNAL(timeout()),this,SLOT(doSliding()));

    m_timerShrink = new QTimer(this);
    m_timerShrink->setInterval(PYSB_SHRINK_TIMER_INTERVAL);
    connect(m_timerShrink,SIGNAL(timeout()),this,SLOT(doShrinking()));

    setFixedHeight(PYSB_HEIGHT);
    setAttribute(Qt::WA_TranslucentBackground);
}

CLSliderButtons::~CLSliderButtons()
{

}


void CLSliderButtons::mousePressEvent(QMouseEvent *event)
{
    int nCountItem = m_vecStrRect.count();
    QString strText;
    for(int nIndex = 0;nIndex < nCountItem ; nIndex++)
    {
        if(m_vecStrRect.at(nIndex).second.contains(event->pos()))
        {
            strText = m_vecStrRect.at(nIndex).first;
            //DEBUG_VAR(strText);

            emit sig_itemClicked(strText);

            m_rectItemTarget = m_vecStrRect.at(nIndex).second;

            if(m_rectItemTarget.width() > m_rectItemDisplayer.width())
            {
                m_bShrink = false;
            }
            else
            {
                m_bShrink = true;
            }

            if(m_rectItemTarget.topLeft().x() > m_rectItemDisplayer.topLeft().x() )
            {
                m_bForward = true;
            }
            else
            {
                m_bForward = false;
            }

            int distance = m_rectItemTarget.topLeft().x() - m_rectItemDisplayer.topLeft().x();
            if(distance < 0)
            {
                distance = 0 - distance;
            }
            QString tmp = QString("%1").arg(distance);
            //DEBUG_VAR(tmp);


            setSlideIncrement(createSlideIncrement((unsigned int)distance)/*PYSB_BAR_SLIDE_INCREMENT_INIT*/);
            m_timerSlide->start();
            m_timerShrink->start();
        }
    }
}

void CLSliderButtons::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    drawBg(&painter);
    drawBar(&painter);
    drawText(&painter);
}

void CLSliderButtons::setSelectItemBGColor(QColor c1, QColor c2)
{
    m_colorItemPoint0=c1;
    m_colorItemPoint1=c2;
}

///
/// \brief CLSliderButton::drawBar
/// \param painter
///
void CLSliderButtons::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BarGradient(m_rectItemDisplayer.topLeft(),m_rectItemDisplayer.bottomLeft());
    BarGradient.setColorAt(0.0,m_colorItemPoint0);
    BarGradient.setColorAt(1.0,m_colorItemPoint1);
    painter->setBrush(BarGradient);

    painter->drawRoundedRect(m_rectItemDisplayer, PYSB_RECT_RADIUS,PYSB_RECT_RADIUS);
    painter->restore();
}

///
/// \brief CLSliderButton::drawBg 画背景 渐变色
/// \param painter
///
void CLSliderButtons::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BgGradient(QPoint(0,0), QPoint(0, height()));
    BgGradient.setColorAt(0.0, COLOR_BG_START);
    BgGradient.setColorAt(1.0, COLOR_BG_END);
    painter->setBrush(BgGradient);
    painter->drawRoundedRect(rect(), PYSB_RECT_RADIUS,PYSB_RECT_RADIUS);
    painter->restore();
}

///
/// \brief CLSliderButton::drawText
/// \param painter
///
void CLSliderButtons::drawText(QPainter *painter)
{
    painter->save();

    painter->setPen(Qt::white);
    QFont fontText;
    fontText.setBold(true);
    painter->setFont(fontText);

    int nCountItem = m_vecStrRect.count();
    QString strText;            // 项的文本
    qreal dOffsetStartX = 0;    // 项的起始坐标
    qreal dItemWidth = 0;       // 项的文本宽度
    for(int nIndex = 0; nIndex < nCountItem; nIndex++)
    {
        strText = m_vecStrRect.at(nIndex).first;
        dItemWidth  = fontMetrics().width(strText);
        QPointF topLeft(dOffsetStartX, 0);
        QPointF bottomRight(dOffsetStartX + dItemWidth + 2 * ITEM_SPACE, height());
        QRectF textRect(topLeft, bottomRight);

        m_vecStrRect[nIndex].second = textRect; //记录该项的rect
        if(m_bVirgin)
        {
            m_rectItemDisplayer = textRect;
            m_bVirgin = false;
        }
        painter->drawText(textRect, strText, Qt::AlignVCenter|Qt::AlignHCenter);

        /// increment initX
        dOffsetStartX += dItemWidth + 2 * ITEM_SPACE;
    }

    // 重新调整控件宽度
    setFixedWidth(dOffsetStartX);
    painter->restore();
}

unsigned int CLSliderButtons::getSlideIncrement()
{
    if(m_unTotalIncrement > 1)
        m_unTotalIncrement --;

    return m_unTotalIncrement;
}

void CLSliderButtons::setSlideIncrement(unsigned int nInc)
{
    m_unTotalIncrement = nInc;
}

///
/// \brief CLSliderButton::createSlideIncrement 根据二次函数产生一个增量，原理:如果x^2 > n, y = 2^(1/2)x, 证明1+2+3+4+……+y > n
/// 证明: z = 1+2+3+4+……+y = (y+1)*y/2 = (2^(1/2)x + 1)*(2^(1/2)x) /2 = ((2n)^(1/2) + 1)*((2n)^(1/2)) / 2
///  = (2n + (2n)^(1/2)) /2 = n + (2n)^(1/2) /2 > n
/// \param nDistance
/// \return
///
unsigned int CLSliderButtons::createSlideIncrement(unsigned int nDistance)
{
    unsigned int n = 1;
    while(1)
    {
        if(n * n > nDistance)
        {
            break;
        }
        else
        {
            n++;
        }
    }
    return n * 1.414;
}

void CLSliderButtons::doSliding()
{

    qreal BarX = m_rectItemDisplayer.topLeft().x();
    qreal BarWidth = m_rectItemDisplayer.width();
    if(m_bForward)
    {
        BarX += getSlideIncrement();
        if(BarX >= m_rectItemTarget.topLeft().x())
        {
            BarX = m_rectItemTarget.topLeft().x();
            m_timerSlide->stop();
        }
    }
    else
    {
        BarX -= getSlideIncrement();
        if(BarX <= m_rectItemTarget.topLeft().x())
        {
            BarX = m_rectItemTarget.topLeft().x();
            m_timerSlide->stop();

        }
    }
    m_rectItemDisplayer = QRectF(QPointF(BarX, 0), QPointF(BarX + BarWidth, height()));
    update();
}

void CLSliderButtons::doShrinking()
{
    qreal BarX = m_rectItemDisplayer.topLeft().x();
    qreal BarWidth = m_rectItemDisplayer.width();

    if(m_bShrink)
    {
        BarWidth -= PYSB_BAR_WIDTH_INCREMENT;

        if(BarWidth < m_rectItemTarget.width())
        {
            m_timerShrink->stop();
        }

    }
    else
    {
        BarWidth += PYSB_BAR_WIDTH_INCREMENT;

        if(BarWidth > m_rectItemTarget.width())
        {
            m_timerShrink->stop();
        }
    }
    m_rectItemDisplayer = QRectF(QPointF(BarX,0),QPointF(BarX + BarWidth,height()));
    update();
}

void CLSliderButtons::addItem(const QString &str)
{
    // 检查是否已经存在该项
    int nCountItem = m_vecStrRect.count();
    for(int nIndex = 0; nIndex < nCountItem ; nIndex++)
    {
        if(m_vecStrRect.at(nIndex).first.toLower() == str.toLower())
        {
            return ;
        }
    }

    m_vecStrRect.push_back(qMakePair(str, QRectF()));
    update();

    if(m_vecStrRect.count() > 0)
    {
        emit sig_itemClicked(m_vecStrRect.at(0).first);
    }

}
