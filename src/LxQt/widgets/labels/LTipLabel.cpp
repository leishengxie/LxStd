#include "LTipLabel.h"

#include <QToolTip>
// #include "LQtFunc.h"

CLTipLabel::CLTipLabel(QWidget *parent)
    :QLabel(parent)
{

}

CLTipLabel::CLTipLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel(text, parent, f)
{

}



void CLTipLabel::enterEvent(QEvent *event)
{
    QToolTip::showText(QCursor::pos(), strRecombineLine(m_strReal));
}

void CLTipLabel::leaveEvent(QEvent *event)
{

}

///
/// \brief CLTipLabel::strRecombineLine 对传入的文本strSrc根据控件pWidget的宽度自动换行
/// \param strSrc
/// \return
///
QString CLTipLabel::strRecombineLine(const QString &strSrc)
{

    QString strResult;
    QFontMetrics fm(fontMetrics());
    int nTextTotalWidthInPxs = fm.width(strSrc);
    if (nTextTotalWidthInPxs <= width())
    {
        strResult = strSrc;
        return strResult;
    }
    // CharNum <==> bytes
    const int nTotalCharNum = strSrc.length();
    int nPickUpStartPos = 0;
    int nOffset = 1;
    QString strPickUp;
    unsigned int nPickUpCharNum = 0;
    unsigned int unPickUpWidthPxs = 0;
    while (nOffset <= nTotalCharNum)
    {
        nPickUpCharNum = nOffset - nPickUpStartPos;
        strPickUp = strSrc.mid(nPickUpStartPos, nPickUpCharNum);
        unPickUpWidthPxs = fm.width(strPickUp);
        if (unPickUpWidthPxs >= width())
        {
            // 换行
            strResult += strPickUp + "\n";
            nPickUpStartPos = nOffset;
            unPickUpWidthPxs = 0;
        }
        ++nOffset;
    }

    // 加上最后一段
    if (!strPickUp.isEmpty())
    {
        strResult += strPickUp;
    }

    return strResult;
}
