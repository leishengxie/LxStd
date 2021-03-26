
#include <QImage>

/*
 * 用户需求:我要写一个窗口基类,以后公司的同事就使用我这个基类来写程序,提供一种统一的风格.
我的思路:美工画了一个窗口背景图片贴到窗口上,但是如果要适应不同大小的窗口的时候,就必须提供好多背景图片,浪费"硬盘"不说也麻烦.
所以我就想在代码里处理一下背景图片以适应不同尺寸的窗口.
注:如果是普通的缩放,背景图片里的窗口标题栏和边框会变宽或窄,界面风格就不统一了.
想要的效果就是改变了图片的大小,但是图片里的标题栏和边框的"宽度"或者"高度"都不变
*/

class CL9GridImageUtil
{
public:
    static QPixmap* create9GridPixmap(const QString& strImgFilePath, QPoint ptGrid1BottomRight, QRect rectDest);
    static QPixmap* create9GridPixmap(const QString &picName, int iHorzSplit, int iVertSplit, int DstWidth, int DstHeight);

    static bool split9Gird(const QRect& rcSrc, QPoint ptGrid1BottomRight, QRect* parrayRect, int nArrayCount = 9);

public:
    // 如果不用静态方法，实例需要loadImage
    bool loadImage(const QString& strImgFilePath, QPoint ptGrid1BottomRight);

    void draw9GridImage(QPainter* painter, QRect rectDraw, int nAlpha);
    QPixmap* create9GridPixmap(QRect rectDest);
    QPixmap* scale(QSize sizeDest);



private:
    QImage m_imgSrc;                    // 资源图片
    QRect  m_arrRectGridImgSrc[9];      // 资源图片的九宫格

};

