#ifndef _L_NUM_KEY_BOARD_H
#define _L_NUM_KEY_BOARD_H

#include <QWidget>
#include "patterns/Singleton.h"

class QLineEdit;
class QTextEdit;
class QPlainTextEdit;
class QTextBrowser;
class QPushButton;
class QTimer;
class QEvent;

namespace Ui
{
class CLNumKeyBoard;
}

///
/// \brief The CLNumKeyBoard class 数字键盘类-单例模式
/// 不提供虚拟键盘拼音模式，qt5.7自带virtualkeyboard
///
class CLNumKeyBoard : public QWidget, public CSingleton<CLNumKeyBoard>
{
    Q_OBJECT

public:
    explicit CLNumKeyBoard(QWidget *parent = 0);
    ~CLNumKeyBoard();

    // 安装本数字键盘
    void install();

    void uninstall();

protected:
    ///
    /// \brief eventFilter 事件过滤器
    /// \param obj
    /// \param event
    /// \return
    ///
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    ///
    /// \brief focusChanged 焦点改变事件槽函数处理
    /// \param oldWidget
    /// \param nowWidget
    ///
    void focusChanged(QWidget *oldWidget, QWidget *nowWidget);
    //输入法面板按键处理
    void btn_clicked();
    //改变输入法面板样式
    void changeStyle(QString topColor, QString bottomColor, QString borderColor, QString textColor);
    //定时器处理退格键
    void reClicked();

private:
    void initProperty();            //初始化属性
    void changeStyle(QString strStyle);             //改变样式

    bool checkPress();              //校验当前长按的按钮
    void insertValue(QString value);//插入值到当前焦点控件
    void deleteValue();             //删除当前焦点控件的一个字符


private:
    Ui::CLNumKeyBoard *ui;

    bool m_bPress;                   //是否长按退格键
    QPushButton *m_pBtnPress;          //长按按钮
    QTimer *m_pTimerPress;             //退格键定时器
    bool m_bFirst;                   //是否首次加载

    QWidget *m_pWgtCur;         //当前焦点的对象
    QLineEdit *m_pLineEditCur;     //当前焦点的单行文本框
    QTextEdit *m_pTextEditCur;     //当前焦点的多行文本框
    QPlainTextEdit *m_pPlainCur;   //当前焦点的富文本框
    QTextBrowser *m_pTextBrowserCur;   //当前焦点的文本浏览框

    QString m_strCurrentEditType;        //当前焦点控件的类型
    QString m_strStyleCur;           //当前输入法面板样式
    int m_nFontSizeCur;            //当前输入法面板字体大小


};

#endif // _L_NUM_KEY_BOARD_H
