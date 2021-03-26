#ifndef __L_SLIDEBUTTON_H
#define __L_SLIDEBUTTON_H

#include <QDebug>
#include <QWidget>
#include <QtGui>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMouseEvent>

///
/// \brief The CLSliderButtons class 滑动按钮组
/// 可以滑动的单选按钮组合，滑动效果为逐渐衰弱
///
class CLSliderButtons : public QWidget
{
    Q_OBJECT
public:
    explicit CLSliderButtons(QWidget *parent = 0);
    ~CLSliderButtons();

public:
    void addItem(const QString& str);
    void setSelectItemBGColor(QColor c1, QColor c2);

signals:
    void sig_itemClicked(const QString& str);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *);
    QSize sizeHint() const
    {
        return QSize(300,50);
    }

private:
    void drawBg(QPainter* painter);
    void drawBar(QPainter* painter);
    void drawText(QPainter* painter);


    unsigned int getSlideIncrement();
    void setSlideIncrement(unsigned int nInc);
    unsigned int createSlideIncrement(unsigned int nDistance);

private slots:
    void doSliding();
    void doShrinking();

private:
    QVector< QPair<QString,QRectF> > m_vecStrRect; // 项列表
    QRectF  m_rectItemDisplayer;// 当前显示项的rect
    QRectF  m_rectItemTarget;   // 下一个目标项rect
    QColor m_colorItemPoint0;   // 显示项的起始渐变色
    QColor m_colorItemPoint1;   // 显示项的结束渐变色


    bool m_bForward;            // 选择项改变时，前行或后退的方向
    bool m_bShrink;             // 选择项改变时，由于每一项的文本长度可能不一样，决定是否收缩或扩张
    bool m_bVirgin;             // 是否初次

    QTimer* m_timerSlide;   // 滑动定时器
    QTimer* m_timerShrink;  // 收缩定时器

    unsigned int m_unTotalIncrement; // 逐渐衰减的增量，本例实现效果的重点




};

#endif // __L_SLIDEBUTTON_H
