#include "NoTitleMenuMainWidget.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <QApplication>
#include <QtDebug>

//CLMoveWidget::CLMoveWidget(QWidget *parent)
//    : QWidget(parent)
//    //, m_wgtRoot(NULL)
//{

//}

CNoTitleMenuMainWidget::CNoTitleMenuMainWidget(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
, m_bCanDrag(false)
, m_pWgtDrag(NULL)
, m_bCanResize(false)
, m_nCanResizeBorder(6)
, m_bCanDragFromChild(false)
{
    initUI();
}

CNoTitleMenuMainWidget::~CNoTitleMenuMainWidget()
{

}

void CNoTitleMenuMainWidget::initUI()
{
    //setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setMinimumSize(100, 50);
    // 要检测窗口是否可以拖动大小形状改变需要让控件在鼠标未按下都能响应鼠标应当事件mouseMoveEvent
    QList<QWidget*> widgetList = findChildren<QWidget*>();
    foreach(QWidget* widget, widgetList)
    {
        widget->setMouseTracking(true);
    }
    qApp->installEventFilter(this);
}

///
/// \brief CLMoveWidget::mouseMoveFunc 本类和子类移动事件公有方法
/// \param object 拥有区分是本类调用还是子类调用
/// \param event
///
void CNoTitleMenuMainWidget::mouseMoveFunc(QObject *object, QMouseEvent *event)
{
    // 优先考虑窗口大小改变
    if (Qt::LeftButton & event->buttons())
    {
        if (m_bCanResize)                    //如果左键按住移动且在拖拽状态
        {
            const QPoint point_offset = event->globalPos() - m_ptGlobalResizeStart;
            m_ptGlobalResizeStart = event->globalPos();
            int nOffsetX1 = ED_LockRight == m_emHorizontal ? point_offset.x() : 0;
            int nOffsetY1 = ED_LockBottom == m_emVertical ? point_offset.y() : 0;
            int nOffsetX2 = ED_LockLeft == m_emHorizontal ? point_offset.x() : 0;
            int nOffsetY2 = ED_LockTop == m_emVertical ? point_offset.y() : 0;
            setGeometry(geometry().adjusted(nOffsetX1, nOffsetY1, nOffsetX2, nOffsetY2));
        }
    }
    else if (Qt::NoButton == event->button())
    {
        //先判断是否光标在可拖拽大小的窗口位置

        // 获取相对于主窗口CNoTitleMenuMainWidget的坐标
        //const QPoint& pos = event->pos(); // 返回的坐标是相对于鼠标所在的这个widget（如QPushButton）的坐标
        /* 方法一
        QPoint posRelative;
        QWidget* widget = qobject_cast<QWidget*>(object);
        if (widget)
        {
        posRelative = widget->mapTo(this, pos); // 将当前窗口坐标转换成指定parent坐标
        }
        */

        // 方法二
        const QPoint& posGlobal= event->globalPos(); // 返回相对于屏幕左上角的全局坐标
        const QPoint& posRelative = mapFromGlobal(posGlobal); // 转换为相对于当前窗口this的窗口坐标

        //qDebug() << pos << posRelative << posGlobal;

        bool bHorLeft = posRelative.x() < m_nCanResizeBorder;
        bool bHorRight = posRelative.x() > rect().right() - m_nCanResizeBorder;
        bool bVertTop = posRelative.y() < m_nCanResizeBorder;
        bool bVertBottom = posRelative.y() > rect().bottom() - m_nCanResizeBorder;
        if (bHorLeft || bHorRight || bVertTop || bVertBottom)
        {
            m_bCanResize = true;
            if (bHorLeft && bVertTop)        //左上角拖拽
            {
                setCursor(Qt::SizeFDiagCursor);
                m_emHorizontal = ED_LockRight;
                m_emVertical = ED_LockBottom;
            }
            else if (bHorLeft && bVertBottom)    //左下角拖拽
            {
                setCursor(Qt::SizeBDiagCursor);
                m_emHorizontal = ED_LockRight;
                m_emVertical = ED_LockTop;
            }
            else if (bHorRight && bVertTop)        //右上角拖拽
            {
                setCursor(Qt::SizeBDiagCursor);
                m_emHorizontal = ED_LockLeft;
                m_emVertical = ED_LockBottom;
            }
            else if (bHorRight && bVertBottom)    //右下角拖拽
            {
                setCursor(Qt::SizeFDiagCursor);
                m_emHorizontal = ED_LockLeft;
                m_emVertical = ED_LockTop;
            }
            else if (bHorLeft)                    //左边框拖拽
            {
                setCursor(Qt::SizeHorCursor);
                m_emHorizontal = ED_LockRight;
                m_emVertical = ED_RemainUnchanged;
            }
            else if (bHorRight)                    //右边框拖拽
            {
                setCursor(Qt::SizeHorCursor);
                m_emHorizontal = ED_LockLeft;
                m_emVertical = ED_RemainUnchanged;
            }
            else if (bVertTop)                    //上边框拖拽
            {
                setCursor(Qt::SizeVerCursor);
                m_emHorizontal = ED_RemainUnchanged;
                m_emVertical = ED_LockBottom;
            }
            else if (bVertBottom)                //下边框拖拽
            {
                setCursor(Qt::SizeVerCursor);
                m_emHorizontal = ED_RemainUnchanged;
                m_emVertical = ED_LockTop;
            }
        }
        else if (m_bCanResize)
        {
            m_bCanResize = false;
            setCursor(Qt::ArrowCursor);            //如果上一次判断修改了光标，不再是拖拽的状态把光标改回来
        }
    }
    if (m_bCanResize)
    {
        return;
    }

    // 考虑窗口移动
    // 如果来自子控件的拖动且不允许子控件移动主窗口则直接返回
    if (!m_bCanDragFromChild && (object != this))
    {
        return;
    }

    if ( m_bCanDrag )
    {
        QPoint movePot = event->globalPos() - m_ptMousePress;

        // move是移动的位置是相对于全局而言(即屏幕)
        QApplication::activeWindow()->move(movePot);
        return;
    }
}

void CNoTitleMenuMainWidget::mousePressFuc(QObject *object, QMouseEvent *event)
{
    // 优先判断是否可以触发窗口形态变化
    if (Qt::LeftButton == event->button() && m_bCanResize)
    {
        m_ptGlobalResizeStart = event->globalPos();
        return;
    }

    // 判断是否可以触发拖动
    // 如果来自子控件的拖动且不允许子控件移动主窗口则直接返回
    if (!m_bCanDragFromChild && (object != this))
    {
        return;
    }

    if (m_pWgtDrag == NULL)
    {
        m_pWgtDrag = this;
    }

    // 同意需要转换为父窗口为本类实例的坐标
    //m_ptMousePress = event->pos(); // 错误
    const QPoint& posGlobal= event->globalPos(); // 返回相对于屏幕左上角的全局坐标
    m_ptMousePress = this->mapFromGlobal(posGlobal); // 转换为相对于当前窗口this的窗口坐标
    QRect rectDrag = m_pWgtDrag->rect();
    if (rectDrag.contains(m_ptMousePress))
    {
        m_bCanDrag = true;
    }
}

void CNoTitleMenuMainWidget::mouseReleaseFuc(QObject *object, QMouseEvent *event)
{
    m_bCanDrag=false;
}


void CNoTitleMenuMainWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    mouseMoveFunc(this, event);
}

void CNoTitleMenuMainWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    mousePressFuc(this, event);
}

void CNoTitleMenuMainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    mouseReleaseFuc(this, event);
}

void CNoTitleMenuMainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

// 当子窗体覆盖当前主窗体时mouseMoveEvent没有被调用
bool CNoTitleMenuMainWidget::eventFilter(QObject *object, QEvent *event)
{
    if (event == nullptr)
    {
        return false;
    }
    if (event->type() == QEvent::None)
    {
        return false;
    }
    if (object == this)
    {
        return QObject::eventFilter(object, event);
    }
//    if (event->type() == QEvent::HoverMove)
//    {
//        mouseMoveFunc(event);
//    }
    // 监听子类的鼠标事件
    if(event->type()==QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        mousePressFuc(object, mouseEvent);
    }
    if(event->type()==QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        mouseMoveFunc(object, mouseEvent);
    }
    if(event->type()==QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        mouseReleaseFuc(object, mouseEvent);
    }
    return QObject::eventFilter(object, event);
}



