#include "LNumKeyBoard.h"
#include "ui_LNumKeyBoard.h"
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QPushButton>
#include <QTimer>
#include <QEvent>
#include <QtDebug>


CLNumKeyBoard::CLNumKeyBoard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CLNumKeyBoard)
    , m_strStyleCur("brown")
    , m_nFontSizeCur(10)
    , m_bFirst(true)
    , m_bPress(false)
    , m_pWgtCur(NULL)
{
    ui->setupUi(this);

    initProperty();//初始化属性


    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);


    m_pTimerPress = new QTimer(this);
    connect(m_pTimerPress, SIGNAL(timeout()), this, SLOT(reClicked()));

    //如果需要更改输入法面板的样式,改变currentStyle这个变量即可
    //blue--淡蓝色  dev--dev风格  black--黑色  brown--灰黑色  lightgray--浅灰色  darkgray--深灰色  gray--灰色  silvery--银色
    changeStyle(m_strStyleCur);//改变样式

    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn)
    {
        connect(b, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    }

}

CLNumKeyBoard::~CLNumKeyBoard()
{
    delete ui;
}

void CLNumKeyBoard::install()
{
    //绑定全局改变焦点信号槽
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)), this, SLOT(focusChanged(QWidget *, QWidget *)));

    //绑定事件过滤器
    qApp->installEventFilter(this);
}

void CLNumKeyBoard::uninstall()
{
    disconnect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)), this, SLOT(focusChanged(QWidget *, QWidget *)));
    qApp->removeEventFilter(this);
}





void CLNumKeyBoard::initProperty()
{
    ui->btn0->setProperty("btnNum", true);
    ui->btn1->setProperty("btnNum", true);
    ui->btn2->setProperty("btnNum", true);
    ui->btn3->setProperty("btnNum", true);
    ui->btn4->setProperty("btnNum", true);
    ui->btn5->setProperty("btnNum", true);
    ui->btn6->setProperty("btnNum", true);
    ui->btn7->setProperty("btnNum", true);
    ui->btn8->setProperty("btnNum", true);
    ui->btn9->setProperty("btnNum", true);
    ui->btn00->setProperty("btnNum", true);

    ui->btnDot->setProperty("btnOther", true);
    ui->btnSpace->setProperty("btnOther", true);
    ui->btnDelete->setProperty("btnOther", true);
}

void CLNumKeyBoard::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{
    //qDebug() << "oldWidget:" << oldWidget << " nowWidget:" << nowWidget;
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget)) {
        //在Qt5和linux系统中(嵌入式linux除外),当输入法面板关闭时,焦点会变成无,然后焦点会再次移到焦点控件处
        //这样导致输入法面板的关闭按钮不起作用,关闭后马上有控件获取焦点又显示.
        //为此,增加判断,当焦点是从有对象转为无对象再转为有对象时不要显示.
        //这里又要多一个判断,万一首个窗体的第一个焦点就是落在可输入的对象中,则要过滤掉
#ifndef __arm__
        if (oldWidget == 0x0 && !m_bFirst) {
            return;
        }
#endif

        m_bFirst = false;
        if (nowWidget->inherits("QLineEdit")) {
            m_pLineEditCur = (QLineEdit *)nowWidget;
            m_strCurrentEditType = "QLineEdit";
            this->setVisible(true);
        } else if (nowWidget->inherits("QTextEdit")) {
            m_pTextEditCur = (QTextEdit *)nowWidget;
            m_strCurrentEditType = "QTextEdit";
            this->setVisible(true);
        } else if (nowWidget->inherits("QPlainTextEdit")) {
            m_pPlainCur = (QPlainTextEdit *)nowWidget;
            m_strCurrentEditType = "QPlainTextEdit";
            this->setVisible(true);
        } else if (nowWidget->inherits("QTextBrowser")) {
            m_pTextBrowserCur = (QTextBrowser *)nowWidget;
            m_strCurrentEditType = "QTextBrowser";
            this->setVisible(true);
        } else if (nowWidget->inherits("QComboBox")) {
            QComboBox *cbox = (QComboBox *)nowWidget;
            //只有当下拉选择框处于编辑模式才可以输入
            if (cbox->isEditable()) {
                m_pLineEditCur = cbox->lineEdit() ;
                m_strCurrentEditType = "QLineEdit";
                this->setVisible(true);
            }
        } else if (nowWidget->inherits("QSpinBox") ||
                   nowWidget->inherits("QDoubleSpinBox") ||
                   nowWidget->inherits("QDateEdit") ||
                   nowWidget->inherits("QTimeEdit") ||
                   nowWidget->inherits("QDateTimeEdit")) {
            m_pWgtCur = nowWidget;
            m_strCurrentEditType = "QWidget";
            this->setVisible(true);
        } else {
            m_pWgtCur = 0;
            m_pLineEditCur = 0;
            m_pTextEditCur = 0;
            m_pPlainCur = 0;
            m_pTextBrowserCur = 0;
            m_strCurrentEditType = "";
            this->setVisible(false);
        }

        QRect rect = nowWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
        pos = nowWidget->mapToGlobal(pos);
        this->setGeometry(pos.x(), pos.y(), this->width(), this->height());
    }

    Q_UNUSED(oldWidget);
}

bool CLNumKeyBoard::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (m_strCurrentEditType != "") {
            if (obj != ui->btnClose) {
                this->setVisible(true);
            }
            m_pBtnPress = (QPushButton *)obj;
            if (checkPress()) {
                m_bPress = true;
                m_pTimerPress->start(500);
            }
        }
        return false;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        m_pBtnPress = (QPushButton *)obj;
        if (checkPress()) {
            m_bPress = false;
            m_pTimerPress->stop();
        }
        return false;
    }
    return QWidget::eventFilter(obj, event);
}

bool CLNumKeyBoard::checkPress()
{
    //只有属于数字键盘的合法按钮才继续处理
    bool num_ok = m_pBtnPress->property("btnNum").toBool();
    bool other_ok = m_pBtnPress->property("btnOther").toBool();
    if (num_ok || other_ok) {
        return true;
    }
    return false;
}

void CLNumKeyBoard::reClicked()
{
    if (m_bPress) {
        m_pTimerPress->setInterval(30);
        m_pBtnPress->click();
    }
}

void CLNumKeyBoard::btn_clicked()
{
    //如果当前焦点控件类型为空,则返回不需要继续处理
    if (m_strCurrentEditType == "") {
        return;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();
    if (objectName == "btnDelete") {
        deleteValue();
    } else if (objectName == "btnClose") {
        this->setVisible(false);
    } else if (objectName == "btnEnter") {
        this->setVisible(false);
    } else if (objectName == "btnSpace") {
        insertValue(" ");
    } else {
        QString value = btn->text();
        insertValue(value);
    }
}

void CLNumKeyBoard::insertValue(QString value)
{
    if (m_strCurrentEditType == "QLineEdit") {
        m_pLineEditCur->insert(value);
    } else if (m_strCurrentEditType == "QTextEdit") {
        m_pTextEditCur->insertPlainText(value);
    } else if (m_strCurrentEditType == "QPlainTextEdit") {
        m_pPlainCur->insertPlainText(value);
    } else if (m_strCurrentEditType == "QTextBrowser") {
        m_pTextBrowserCur->insertPlainText(value);
    } else if (m_strCurrentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(value));
        QApplication::sendEvent(m_pWgtCur, &keyPress);
    }
}

void CLNumKeyBoard::deleteValue()
{
    if (m_strCurrentEditType == "QLineEdit") {
        m_pLineEditCur->backspace();
    } else if (m_strCurrentEditType == "QTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = m_pTextEditCur->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (m_strCurrentEditType == "QPlainTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = m_pPlainCur->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (m_strCurrentEditType == "QTextBrowser") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = m_pTextBrowserCur->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (m_strCurrentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier, QString());
        QApplication::sendEvent(m_pWgtCur, &keyPress);
    }
}

void CLNumKeyBoard::changeStyle(QString strStyle)
{
    m_strStyleCur = strStyle;
    if (m_strStyleCur == "blue") {
        changeStyle("#DEF0FE", "#C0DEF6", "#C0DCF2", "#386487");
    } else if (m_strStyleCur == "dev") {
        changeStyle("#C0D3EB", "#BCCFE7", "#B4C2D7", "#324C6C");
    } else if (m_strStyleCur == "gray") {
        changeStyle("#E4E4E4", "#A2A2A2", "#A9A9A9", "#000000");
    } else if (m_strStyleCur == "lightgray") {
        changeStyle("#EEEEEE", "#E5E5E5", "#D4D0C8", "#6F6F6F");
    } else if (m_strStyleCur == "darkgray") {
        changeStyle("#D8D9DE", "#C8C8D0", "#A9ACB5", "#5D5C6C");
    } else if (m_strStyleCur == "black") {
        changeStyle("#4D4D4D", "#292929", "#D9D9D9", "#CACAD0");
    } else if (m_strStyleCur == "brown") {
        changeStyle("#667481", "#566373", "#C2CCD8", "#E7ECF0");
    } else if (m_strStyleCur == "silvery") {
        changeStyle("#E1E4E6", "#CCD3D9", "#B2B6B9", "#000000");
    }
}

void CLNumKeyBoard::changeStyle(QString topColor, QString bottomColor, QString borderColor, QString textColor)
{
    QStringList qss;
    qss.append(QString("QWidget#CLNumKeyBoard{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append("QPushButton{padding:5px;border-radius:3px;}");
    qss.append(QString("QPushButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append(QString("QLabel,QPushButton{font-size:%1pt;color:%2;}")
               .arg(m_nFontSizeCur).arg(textColor));
    qss.append(QString("QPushButton#btnPre,QPushButton#btnNext,QPushButton#btnClose{padding:5px;}"));
    qss.append(QString("QPushButton{border:1px solid %1;}")
               .arg(borderColor));
    qss.append(QString("QLineEdit{border:1px solid %1;border-radius:5px;padding:2px;background:none;selection-background-color:%2;selection-color:%3;}")
               .arg(borderColor).arg(bottomColor).arg(topColor));
    setStyleSheet(qss.join(""));
}
