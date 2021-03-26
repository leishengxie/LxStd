#include "L9GridImageUtil.h"
#include <QPainter>

/*
*   1 * 2 * 3
*   * * * * *
*   4 * 5 * 6
*   * * * * *
*   7 * 8 * 9
9宫格缩放规则如下：
1、将一张图分割成9块,不一定是平均分，但四个角上的格子大小是始终是一样的
2、四个角(1,3,7,9)在缩放的时候是保持大小不变
3、图块2，8仅当宽度变化时缩放宽度。
4、图块4，6仅当高度变化时缩放高度。
5、图块5当图片大小发生变化，宽度和高度都进行缩放。
*/

///
/// \brief CSpliter9GridImage::setImage 设置图片
/// \param strImgFilePath  图片路径
/// \param ptGrid1BottomRight 第一个格子左下角坐标
/// \return
///
bool CL9GridImageUtil::loadImage(const QString& strImgFilePath, QPoint ptGrid1BottomRight)
{            
    if (!m_imgSrc.load(strImgFilePath))
    {
        return false;
    }
    int nImageWidth = m_imgSrc.width();
    int nImageHeight = m_imgSrc.height();
    // 得到m_arrRectImgSrcGrid
    return split9Gird(QRect(0, 0, nImageWidth, nImageHeight), ptGrid1BottomRight, m_arrRectGridImgSrc, 9);
}

///
/// \brief CL9GridImageUtil::split9Gird
/// \param rect
/// \param ptGrid1BottomRight
/// \param parrayRect
/// \param nArrayCount
/// \return
///
bool CL9GridImageUtil::split9Gird(const QRect& rect, QPoint ptGrid1BottomRight, QRect* parrayRect, int nArrayCount)
{
    if (nArrayCount != 9)
        return false;
    QRect* arrayRect = parrayRect;
    int nWidth = rect.width();
    int nHeight = rect.height();
    if (ptGrid1BottomRight.x() <= 0)
        return false;
    if (ptGrid1BottomRight.y() <= 0)
        return false;
    if (ptGrid1BottomRight.x() >= nWidth / 2)
        return false;
    if (ptGrid1BottomRight.y() >= nHeight / 2)
        return false;

    // x1为第一个格子左上x坐标……
    int x1 = rect.left() + 0;
    int x2 = rect.left() + ptGrid1BottomRight.x();
    int x3 = rect.left() + nWidth - ptGrid1BottomRight.x();
    int x4 = rect.left() + nWidth;
    int y1 = rect.top() + 0;
    int y2 = rect.top() + ptGrid1BottomRight.y();
    int y3 = rect.top() + nHeight - ptGrid1BottomRight.y();
    int y4 = rect.top() + nHeight;

    arrayRect[0] = QRect(QPoint(x1, y1), QPoint(x2, y2));
    arrayRect[1] = QRect(QPoint(x2 + 1, y1), QPoint(x3, y2));
    arrayRect[2] = QRect(QPoint(x3 + 1, y1), QPoint(x4, y2));
    arrayRect[3] = QRect(QPoint(x1, y2 + 1), QPoint(x2, y3));
    arrayRect[4] = QRect(QPoint(x2 + 1, y2 + 1), QPoint(x3, y3));
    arrayRect[5] = QRect(QPoint(x3 + 1, y2 + 1), QPoint(x4, y3));
    arrayRect[6] = QRect(QPoint(x1, y3 + 1), QPoint(x2, y4));
    arrayRect[7] = QRect(QPoint(x2 + 1, y3 + 1), QPoint(x3, y4));
    arrayRect[8] = QRect(QPoint(x3 + 1, y3 + 1), QPoint(x4, y4));
    return true;
}


///
/// \brief CSpliter9GridImage::draw9GridImage 在目标设备上绘制九宫格图
/// \param p QPainter 指定的设备上
/// \param rectDraw
/// \param nAlpha
///
void CL9GridImageUtil::draw9GridImage(QPainter* painter, QRect rectDraw, int nAlpha)
{
    // 根据rectDraw得到新的九宫格格子arrayGirdDest
    QRect arrayGirdDest[9];
    split9Gird(rectDraw, m_arrRectGridImgSrc[0].bottomRight(), arrayGirdDest, 9);

    for (int i = 0; i < 9; i++)
    {
        const QRect& rcSrc = m_arrRectGridImgSrc[i];
        const QRect& rcDest = arrayGirdDest[i];
        painter->drawImage(rcDest, m_imgSrc, rcSrc);
    }
}

QPixmap *CL9GridImageUtil::create9GridPixmap(QRect rectDest)
{
    QRect arrayGirdDest[9];
    split9Gird(rectDest, m_arrRectGridImgSrc[0].bottomRight(), arrayGirdDest, 9);

    QPixmap pixSrc = QPixmap::fromImage(m_imgSrc);
    QPixmap* pixResult = new QPixmap(rectDest.size());
    QPainter painter(pixResult);
    for (int i = 0; i < 9; ++i)
    {
        QPixmap pixGird = pixSrc.copy(m_arrRectGridImgSrc[i]);
        painter.drawPixmap(arrayGirdDest[i], pixGird);
    }
    return pixResult;
}

// 是在相对资源图基础上进行缩放
QPixmap *CL9GridImageUtil::scale(QSize sizeDest)
{
    QRect rectDest(QPoint(0, 0), sizeDest);
    return create9GridPixmap(rectDest);
}


///
/// \brief CL9GridImageUtil::create9GridPixmap
/// \param strImgFilePath
/// \param ptGrid1BottomRight
/// \param rectDest
/// \return
///
QPixmap *CL9GridImageUtil::create9GridPixmap(const QString &strImgFilePath, QPoint ptGrid1BottomRight, QRect rectDest)
{
    QPixmap pixSrc;
    if (!pixSrc.load(strImgFilePath))
    {
        return 0;
    }
    QPixmap* pixResult = new QPixmap(rectDest.size());
    QRect arrayGirdSrc[9];
    QRect arrayGirdDest[9];

    split9Gird(QRect(0, 0, pixSrc.width(), pixSrc.height()), ptGrid1BottomRight, arrayGirdSrc, 9);
    split9Gird(rectDest, ptGrid1BottomRight, arrayGirdDest, 9);

    QPainter painter(pixResult);
    for (int i = 0; i < 9; ++i)
    {
        painter.drawPixmap(arrayGirdDest[i], *pixResult, arrayGirdSrc[i]);
    }
    return pixResult;
}

/*
**  功能             : 九宫格图处理
**  picName          : 图片名字
**  iHorzSplit       : 四个角上格子的宽度
**  iVertSplit       : 四个角上格子的高度
**  DstWidth         : 整个图片缩放的宽度
**  DstHeight         : 整个图片缩放的高度
**  返回值           : 处理完成的图片
*/
///------此方法相对前一种不太灵活, 需要单个处理第2，4，5，6，8的格子
QPixmap* CL9GridImageUtil::create9GridPixmap(const QString &picName, int iHorzSplit, int iVertSplit, int DstWidth, int DstHeight)
{
    QPixmap* pix = new QPixmap(picName);

    int pixWidth = pix->width();
    int pixHeight = pix->height();

    QPixmap pix_1 = pix->copy(0, 0, iHorzSplit, iVertSplit);
    QPixmap pix_2 = pix->copy(iHorzSplit, 0, pixWidth-iHorzSplit*2, iVertSplit);
    QPixmap pix_3 = pix->copy(pixWidth-iHorzSplit, 0, iHorzSplit, iVertSplit);

    QPixmap pix_4 = pix->copy(0, iVertSplit, iHorzSplit, pixHeight-iVertSplit*2);
    QPixmap pix_5 = pix->copy(iHorzSplit, iVertSplit, pixWidth-iHorzSplit*2, pixHeight-iVertSplit*2);
    QPixmap pix_6 = pix->copy(pixWidth-iHorzSplit, iVertSplit, iHorzSplit, pixHeight-iVertSplit*2);

    QPixmap pix_7 = pix->copy(0, pixHeight-iVertSplit, iHorzSplit, iVertSplit);
    QPixmap pix_8 = pix->copy(iHorzSplit, pixHeight-iVertSplit, pixWidth-iHorzSplit*2, pixWidth - iHorzSplit*2);
    QPixmap pix_9 = pix->copy(pixWidth-iHorzSplit, pixHeight-iVertSplit, iHorzSplit, iVertSplit);

    pix_2 = pix_2.scaled(DstWidth-iHorzSplit*2,iVertSplit, Qt::IgnoreAspectRatio);//保持高度拉宽
    pix_4 = pix_4.scaled(iHorzSplit, DstHeight-iVertSplit*2, Qt::IgnoreAspectRatio);//保持宽度拉高
    pix_5 = pix_5.scaled(DstWidth-iHorzSplit*2,DstHeight-iVertSplit*2, Qt::IgnoreAspectRatio);
    pix_6 = pix_6.scaled(iHorzSplit, DstHeight-iVertSplit*2, Qt::IgnoreAspectRatio);//保持宽度拉高
    pix_8 = pix_8.scaled(DstWidth-iHorzSplit*2, iVertSplit);//保持高度拉宽


    QPixmap* resultImg =new QPixmap(DstWidth, DstHeight);
    QPainter* painter = new QPainter(resultImg);
    if (!resultImg->isNull()) {
        painter->drawPixmap(0,0,pix_1);
        painter->drawPixmap(iHorzSplit, 0, pix_2);
        painter->drawPixmap(DstWidth-iHorzSplit,0,pix_3);

        painter->drawPixmap(0, iVertSplit, pix_4);
        painter->drawPixmap(iHorzSplit, iVertSplit, pix_5);
        painter->drawPixmap(DstWidth-iHorzSplit, iVertSplit, pix_6);

        painter->drawPixmap(0, DstHeight-iVertSplit, pix_7);
        painter->drawPixmap(iHorzSplit, DstHeight-iVertSplit, pix_8);
        painter->drawPixmap(DstWidth-iHorzSplit, DstHeight-iVertSplit, pix_9);
        painter->end();
    }
    return resultImg;
}


