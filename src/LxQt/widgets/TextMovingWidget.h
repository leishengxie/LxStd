#ifndef TEXTMOVINGWIDGET_H
#define TEXTMOVINGWIDGET_H
#include <QWidget>

class QTimer;


///
/// \brief The TextMovingWidget class 跑马灯（走马灯）horse race lamp
/// 用途，当文字过长大于显示的控件时，需要移动文字展示全部内容
/// back and forth 来回的移动
class CLTextMovingWidget : public QWidget
{
    Q_OBJECT

public:
    enum E_MoveType
    {
        EM_HorseRaceLamp, // 跑马灯（走马灯）horse race lamp
        EM_BackAndForth, // 左右来回的移动
    };

    enum E_MoveDirection
    {
        EM_LeftToRight, // 文本从左向右移动
        EM_RightToLeft
    };

    CLTextMovingWidget(const QString str, E_MoveType eMoveType = EM_BackAndForth, QWidget *parent = 0);
    ~CLTextMovingWidget();

signals:
    void sigMoveDirectionChanged();

public:

    void setText(const QString & strText);

    void setMoveType(E_MoveType eMoveType);

    void setTittleTextNeedMove(bool bNeed);

    int textWidth() const;
protected:
    virtual void paintEvent(QPaintEvent*);


private slots:
    void slot_updateTextGeometry();

private:
    void updateMoveDirection();

private:
    // 定时器
    QTimer *m_pTimer;

    // 要显示的文本
    QString m_strText;

    // 移动类型
    E_MoveType m_eMoveType;

    // 上次的移动方向
    E_MoveDirection m_eMoveDirectionPre;

    // 当前移动方向
    E_MoveDirection m_eMoveDirectionCur;

    // left margin
    int m_nX;

    // 当文本宽度不超过显示控件的宽度时 是否移动显示
    bool m_bTittleTextNeedMove;
};

#endif // TEXTMOVINGWIDGET_H
