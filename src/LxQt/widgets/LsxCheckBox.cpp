#include "LsxCheckBox.h"
#include <QPainter>
#include <QPixmap>
#include <QtDebug>

CLsxCheckBox::CLsxCheckBox(QWidget *parent)
    : QWidget(parent)
{
    init();
}

CLsxCheckBox::CLsxCheckBox(const QString &text, QWidget *parent)
    : m_strText(text)
    , QWidget(parent)
{
    init();
}

CLsxCheckBox::CLsxCheckBox(const QString &strText, QString strImgBg, QString strImgChecked, QWidget *parent)
    : QWidget(parent)
    , m_strText(strText)
    , m_strImgBg(strImgBg)
    , m_strImgChecked(strImgChecked)
{
    init();
}


void CLsxCheckBox::init()
{
    m_bChecked = false;
    m_RectImg = QRect(0, 0, 16, 16);
    int nTextWidth  = fontMetrics().width(m_strText);
    int nTextHeight = fontMetrics().height();
    nTextHeight = nTextHeight > m_RectImg.height() ? nTextHeight : m_RectImg.height();
    setFixedSize(QSize(m_RectImg.width() + SPACE_TEXT + nTextWidth, nTextHeight)); //此处不能用resize
    qDebug() << "MyCheckBox" << rect().x() << rect().y() << rect().width() << rect().height();
    update();
}

CLsxCheckBox::~CLsxCheckBox()
{

}

void CLsxCheckBox::setChecked(bool bChecked)
{
    m_bChecked = bChecked;
    update();
}

void CLsxCheckBox::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pixmap;
    if (m_strImgBg.isEmpty())
    {
        painter.drawRect(m_RectImg);
    }
    else
    {
        pixmap.load(m_strImgBg);
        painter.drawPixmap(m_RectImg, pixmap);
    }

    if (m_bChecked)
    {
        if (m_strImgChecked.isEmpty())
        {
            painter.drawEllipse(m_RectImg);
        }
        else
        {
            pixmap.load(m_strImgChecked);
            painter.drawPixmap(QRect(m_RectImg.left() + m_RectImg.width()/4, m_RectImg.top() + m_RectImg.height() / 4,
                                     m_RectImg.width() / 2, m_RectImg.height() / 2), pixmap);
        }
    }
    else
    {
        //pixmap.fill(Qt::white);
        //painter.drawPixmap(rect(), pixmap);
    }

    QPointF topLeft(m_RectImg.width() + SPACE_TEXT, 0);
    QPointF bottomRight(rect().width(), rect().height());
    QRectF textRect(topLeft, bottomRight);
    painter.drawText(textRect, m_strText,Qt::AlignVCenter|Qt::AlignHCenter);


}

void CLsxCheckBox::mousePressEvent(QMouseEvent *e)
{

}

void CLsxCheckBox::mouseReleaseEvent(QMouseEvent *e)
{
    m_bChecked = !m_bChecked;
    emit clicked(m_bChecked);
    update();
}



//void MyCheckBox::event(QEvent *e)
//{

//}

