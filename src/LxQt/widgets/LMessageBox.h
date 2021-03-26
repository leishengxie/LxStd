#ifndef MIDEAMSGBOX_H
#define MIDEAMSGBOX_H

#include <QDialog>
#include <QMessageBox>

#define TIPSTR   QObject::tr("")
#define LEFTSTR  QObject::tr("取消")
#define RIGHTSTR QObject::tr("确定")

namespace Ui {
class CLMessageBox;
}

class QDialogButtonBox;

enum E_MideaBtn
{
    EM_Ok,
    EM_Cancel
};

///
/// \brief The CLMessageBox class 根据QMessageBox的方式自定制界面
///
class CLMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit CLMessageBox(QString strTitle, QString strContent, QWidget *parent = 0);
    explicit CLMessageBox(QString strTitle, QString strContent, QString leftBtnText, QString rightBtnText, QWidget *parent = 0, bool showCloseBtn = false);
    explicit CLMessageBox(QWidget *parent = 0, const QString &title = tr("Tip"), const QString &text = ""
            ,QMessageBox::StandardButtons buttons = QMessageBox::Ok
            , QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

//    //default construct
//    explicit CMideaMsgBox(QWidget *parent = Q_NULLPTR);
//    //like QMessageBox construct
//    CMideaMsgBox(Icon icon, const QString &title, const QString &text,
//                StandardButtons buttons = NoButton, QWidget *parent = Q_NULLPTR,
//                Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ~CLMessageBox();
    void init();

    QAbstractButton *clickedButton() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;

    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);

    QMessageBox::StandardButton showWarning(QWidget *parent, const QString &title,
                                            const QString &text, QMessageBox::StandardButtons buttons,
                                            QMessageBox::StandardButton defaultButton);

    static E_MideaBtn warning(QWidget *parent, QString strTitle = TIPSTR, QString strContent = "",
                              QString leftBtnText=LEFTSTR, QString rightBtnText=RIGHTSTR, bool showCloseBtn = false);
	
    E_MideaBtn clickedBtn()
    {
        return m_eMideaBtn;
    }

    void setContent(const QString &strContent);

    void showLeftBtn(bool isShowLeftBtn);

    void show();

private slots:
    void onButtonClicked(QAbstractButton *button);
    void slotOkClicked();
    void slotCancelClicked();
    void slot_languageChanged();
    void on_toolButton_clicked();

signals:
    void cancelSignal();
    void okSignal();
private:
    int execReturnCode(QAbstractButton *button);

private:
    Ui::CLMessageBox *ui;

    QDialogButtonBox *m_pButtonBox;
    QAbstractButton *m_pClickedButton;
    QAbstractButton *m_pDefaultButton;
    E_MideaBtn m_eMideaBtn;
};

#endif // MIDEAMSGBOX_H
