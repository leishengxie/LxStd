#ifndef _L_LOADING_WIDGET_H
#define _L_LOADING_WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMap>

struct Location
{
public:
    explicit Location(float _x,float _y)
    {
        x=_x;
        y=_y;
    }
    float x;
    float y;
};

///
/// \brief The CLLoadingWidget class 等待加载控件
/// dot-点，画点动画
///
class CLLoadingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLLoadingWidget(QWidget *parent = nullptr);
    //设置圆点个数
    void setDotCount(int);
    //设置点颜色
    void setDotColor(const QColor&);
    //开始
    void start();
    //设置圆点最大直径
    void setMaxDiameter(float);
    //设置圆点最小直径
    void setMinDiameter(float);

    virtual QSize sizeHint() const;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);


private slots:
    void refresh();

private:
    //绘制圆点
    void paintDot(QPainter &);


    //计算
    void caculate();

private:
    //刷新计数
    int m_nIndex;
    //点的颜色
    QColor m_colorDot;
    //点的个数
    int m_nCountDot;
    //圆点最小直径
    float m_fMinDiameterDot;
    //圆点最大直径
    float m_fMaxDiameterDot;

    int m_Interval; //时间间隔 单位：毫秒(ms)
    //定时器
    QTimer m_timer;
    //绘制区域边长
    float m_fSideWidth;
    //圆的直径
    float m_fCenterDistance;
    //点半径列表, 所有点的半径按某一差值从大到小排列
    QList<float> m_listRadii;
    //圆点坐标列表
    QList<Location> m_listLocation;


};

#endif // _L_LOADING_WIDGET_H
