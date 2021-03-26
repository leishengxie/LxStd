#ifndef CLPROGRESSINDICATOR_H
#define CLPROGRESSINDICATOR_H

#include <QWidget>
#include <QColor>

///
/// \brief The CLProgressIndicator class 等待提示框(进程指示器)
///
class CLProgressIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int delay READ animationDelay WRITE setAnimationDelay)
    Q_PROPERTY(bool displayedWhenStopped READ isDisplayedWhenStopped WRITE setDisplayedWhenStopped)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    CLProgressIndicator(QWidget* parent = 0);

    ///属性函数
    int animationDelay() const { return m_nDelay; }
    void setAnimationDelay(int delay);

    bool isDisplayedWhenStopped() const;
    void setDisplayedWhenStopped(bool state);

    const QColor & color() const { return m_color; }
    void setColor(const QColor & color);

    // 是否正在动画
    bool isAnimated () const;

    virtual QSize sizeHint() const;


public slots:

    void startAnimation();

    void stopAnimation();







    void onProgress(short progress) { m_nProgress = progress; }

signals:
    void finished(void);

protected:

    virtual void timerEvent(QTimerEvent * event);
    virtual void paintEvent(QPaintEvent * event);

private:
    QRect rectDraw();

private:

    unsigned int m_unAngle;             // 当前选择角度
    int m_nIdTimer;                     // 定时器id
    int m_nDelay;                       // 定时器触发时间间隔
    bool m_bDisplayedWhenStopped;       // 动画结束sh是否隐藏本进程指示器实例
    QColor m_color;                     // 进程指示器颜色
    short m_nProgress;                  // 进程指示器的进度值
};



#endif 
