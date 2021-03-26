#include "LsxRadioButton.h"
#include <QPainter>
#include <QMouseEvent>

CLsxRadioButton::CLsxRadioButton(const QString text, QWidget *parent)
    : QWidget(parent)
    , m_text(text)
    , m_rect(QRect(0, 0, 120, 25))
    , m_bMousePress(false)
    , m_eBtnStatus(EB_Normal)
{
    //, m_rect(QRect(0, 0, 90, 25))
    setFixedSize(m_rect.size());
    initColor();
}

void CLsxRadioButton::setBtnStatus(CLsxRadioButton::E_Btn_Status eBtnStatus)
{
    m_eBtnStatus = eBtnStatus;
    update();
}

void CLsxRadioButton::setPress(bool bPress)
{
    m_bMousePress = bPress;
    if (m_bMousePress)
    {
        m_eBtnStatus = EB_Press;
    }
    else
    {
        m_eBtnStatus = EB_Normal;
    }
    update();
}

void CLsxRadioButton::initColor()
{
    m_colorBgNomal = QColor(0,0,0);
    m_colorBgHover = QColor(0,0,0);
    m_colorBgPress = QColor(0,0,0);
    m_colorTextNomal = QColor(255,255,255);
    m_colorTextHover = QColor(6,164,166);
    m_colorTextPress = QColor(6,164,166);
    m_strImgNormal = ":/img/btn_style_normal.png";
    m_strImgHover = ":/img/btn_style_normal.png";
    m_strImgPress = ":/img/btn_style_down.png";
}

void CLsxRadioButton::setTextColor(QColor colorNomal, QColor colorHover, QColor colorPress)
{
    m_colorBgNomal = colorNomal;
    m_colorBgHover = colorHover;
    m_colorBgPress = colorPress;
}

void CLsxRadioButton::setBgColor(QColor colorNomal, QColor colorHover, QColor colorPress)
{
    m_colorTextNomal = colorNomal;
    m_colorTextHover = colorHover;
    m_colorTextPress = colorPress;
}

void CLsxRadioButton::setBgImg(QString strImgNormal, QString strImgHover, QString strImgPress)
{
    m_strImgNormal = strImgNormal;
    m_strImgHover = strImgHover;
    m_strImgPress = strImgPress;
}

void CLsxRadioButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QPixmap pixmap;
    QString imgPath;
    switch (m_eBtnStatus) {
    case EB_Normal:
        //p.setBrush(Qt::darkYellow);        //用画刷来画自己喜欢的颜色
        p.setPen(m_colorTextNomal);
        imgPath = m_strImgNormal;
        //p.setPen(Qt::red);
        break;
    case EB_Hover:
        //p.setBrush(Qt::darkGreen);
        p.setPen(m_colorTextHover);
        imgPath = m_strImgHover;
        break;
    case EB_Press:
        //p.setBrush(Qt::red);
        p.setPen(m_colorTextPress);
        imgPath = m_strImgPress;
        break;
    default:
        break;
    }
    if (!imgPath.isEmpty())
    {
        pixmap.load(imgPath);
        p.drawPixmap(rect(), pixmap);
    }
    else
    {
        p.drawEllipse(m_rect); //  有4个参数，分别是位置和长宽，如果长和宽相等就是一个标准的圆了
    }
    p.drawText(m_rect,m_text,QTextOption(Qt::AlignCenter)); //设置文本有三个参数，分别是 对象，文本，文本位置

}

void CLsxRadioButton::enterEvent(QEvent *e)
{
    if (m_bMousePress)
    {
        return;
    }
    m_eBtnStatus = EB_Hover;
    update();
}

void CLsxRadioButton::leaveEvent(QEvent *e)
{
    if (m_bMousePress)
    {
        return;
    }
    m_eBtnStatus = EB_Normal;
        update();
}

void CLsxRadioButton::mousePressEvent(QMouseEvent *e)
{
    //m_eBtnStatus = EB_Press;
    //update();             //点击一下更新一下，调用painEvent
    if(e->button() == Qt::LeftButton)
        {
            m_bMousePress = true;
            m_eBtnStatus = EB_Press;
            clicked();
            clicked(this);
            update();
        }
}

//void CLsxRadioButton::mouseMoveEvent(QMouseEvent *e)
//{
//    m_eBtnStatus = EB_Hover;
//    update();
//}

void CLsxRadioButton::mouseReleaseEvent(QMouseEvent *e)
{
//    //若点击鼠标左键响应
//        if(m_bMousePress && this->rect().contains(e->pos()))
//        {
//            m_bMousePress = false;
//            m_eBtnStatus = EB_Hover;
//            update();
//            emit clicked();
//        }
}

