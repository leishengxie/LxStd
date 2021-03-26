#ifndef GMPOPERATETIP_H
#define GMPOPERATETIP_H

#include <QFrame>
#include <QWidget>
#include <QTimer>
#include <QGraphicsOpacityEffect>


class QString;
class QLabel;
class QHBoxLayout;
class QPropertyAnimation;


class CLOperateTip : public QWidget
{
    Q_OBJECT

public:
    enum AnimationMode
    {
        AM_NULL,
        AM_FADEOUT,//淡出
        AM_FLYOUT,//飞出
        AM_ZOOMIN,//最小化
    };

    enum Direction
    {
        D_NULL,
        D_LEFT,
        D_TOP,
        D_RIGHT,
        D_BOTTOM,
    };

public:
    static void fadeOut(QWidget * parent = nullptr, QString strText = "", const unsigned int nShowTime = 4000,
                        const unsigned int nAnimationTime = 500);
    static void flyOut(QWidget * parent = nullptr, QString strText = "", Direction direction = D_TOP,
                       const unsigned int nShowTime = 4000, const unsigned int nAnimationTime = 500);
    static void colorize(QWidget * parent = nullptr, QString strText = "", const QColor & color = QColor(20, 142, 53),
                         AnimationMode animation = AM_FLYOUT, Direction direction = D_TOP,
                         const unsigned int nShowTime = 4000, const unsigned int nAnimationTime = 500);
    static void waring(QWidget * parent = nullptr, QString strText = "", const unsigned int nShowTime = 4000,
                       const unsigned int nAnimationTime = 500);
    static void success(QWidget * parent = nullptr, QString strText = "", const unsigned int nShowTime = 4000,
                        const unsigned int nAnimationTime = 500);

public:
    CLOperateTip(QWidget *parent = 0);
    virtual ~CLOperateTip();

public:
    void setText(const QString & text);
    void setIcon(const QString & icon);

    void setBackgroundColor(const QColor & color);

    void setAnimationMode(AnimationMode mode);
    void setFlyoutDirection(Direction direction);

    void setShadowEnable(bool enable);

    void setAnimationdDuration(int duration);
    void setStayTime(int time);

protected:
    virtual bool event(QEvent *) override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void layoutIconAndLabel(QHBoxLayout *);

//	virtual bool eventFilter(QObject *, QEvent *) override;
//	virtual void enterEvent(QEvent *) override;
//	virtual void leaveEvent(QEvent *) override;
//	virtual void showEvent(QShowEvent *) override;
//	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) override;

private:
    void initUI();
    void initConnect();

    void zoomIn();      //缩小
    void moveOut();     //移出
    void fade();        //淡出

private:
    AnimationMode				m_eMode;                    //
    Direction					m_eDirection;               //
    int							m_DurationTime;             // 动画持续时长
    int							m_iStayDuration;            // 窗口停留时长
    QTimer						m_StayTimer;                // 停留控制定时器

    QLabel *					m_pLabelIcon;               // 消息框图标
    QLabel *					m_pLabelText;               // 消息内容
    QWidget *					m_pMoveWidget;              //

    QPropertyAnimation *		m_pPropertyAnim;            // 属性动画
    QGraphicsOpacityEffect *	m_pOpacityEffect;           // 透明效果
    QGraphicsDropShadowEffect * m_pDropShadowEffect;        // 阴影效果，用于增加立体感
    QGraphicsBlurEffect *		m_pBlur;                    // 产生模糊效果,setBlurRadius(qreal blurRadius),数值越大越模糊
    QGraphicsColorizeEffect *	m_pColorize;                // 着色功能。主要函数是setColor和setStrength，指定了着色和着色强度
};

#endif // GMPOPERATETIP_H

