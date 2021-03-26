#ifndef __NO_TITLE_MENU_MAIN_WIDGET_H
#define __NO_TITLE_MENU_MAIN_WIDGET_H
#include <QWidget>

enum E_DragAbsolutePosition
{
    ED_RemainUnchanged=0,
    ED_LockLeft,
    ED_LockTop=1,
    ED_LockRight,
    ED_LockBottom=2
};

class CNoTitleMenuMainWidget : public QWidget
{
    Q_OBJECT
public:
    //explicit CLMoveWidget(QWidget *parent = 0);
    explicit CNoTitleMenuMainWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~CNoTitleMenuMainWidget();

signals:

public slots:
protected:
    //改写QWidget的函数，自己重新实现拖动操作
    void mouseMoveEvent( QMouseEvent * event);
    void mousePressEvent( QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject * object, QEvent * event);
//    void setRootWidget(QWidget* wgtRoot)
//    {
//        m_wgtRoot = wgtRoot;
//    }
    void setRectWidgetDrag(QWidget* pWgtDrag)
    {
        m_pWgtDrag = pWgtDrag;
    }

    void setCanDragFromChild(bool bCanDrag)
    {
        m_bCanDragFromChild = bCanDrag;
    }

private:
    void initUI();

    void mouseMoveFunc(QObject *object, QMouseEvent * event);
    void mousePressFuc(QObject *object, QMouseEvent* event);
    void mouseReleaseFuc(QObject *object, QMouseEvent* event);

protected:
    // 鼠标按下的位置
    QPoint m_ptMousePress;

    // 是否可以拖动窗口
    bool m_bCanDrag;

    // 鼠标按在某个控件的区域上可以拖动窗口，默认指定整个窗口，如果是其他窗口部件如titleBar，该窗口部件的父窗口最好是本类的对象
    QWidget* m_pWgtDrag;

    // 窗口是否可以拖动形变
    bool m_bCanResize;

    // 可以出发窗口形变改变的边框大小
    int m_nCanResizeBorder;

    // 出发窗口形变大小的开始全局坐标
    QPoint m_ptGlobalResizeStart;

    E_DragAbsolutePosition m_emHorizontal;

    E_DragAbsolutePosition m_emVertical;

    bool m_bCanDragFromChild;
};

#endif // __NO_TITLE_MENU_MAIN_WIDGET_H
