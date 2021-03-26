

#include "LMessageBox.h"
#include "ui_LMessageBox.h"
#include <QMessageBox>
#include <QDialogButtonBox>


CLMessageBox::CLMessageBox(QString strTitle, QString strContent, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CLMessageBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    //ui->label->setText(strTitle);
    setWindowTitle(strTitle);
    ui->labelText->setText(strContent);
    //ui->toolButton->hide();
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(slotCancelClicked()));
    connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(slotOkClicked()));
     //connect(I18N::GetInstance(), SIGNAL(languageChanged()), this, SLOT(slot_languageChanged()));

}

CLMessageBox::CLMessageBox(QString strTitle, QString strContent, QString leftBtnText, QString rightBtnText, QWidget *parent, bool showCloseBtn)
    : QDialog(parent)
    , ui(new Ui::CLMessageBox)
{
    ui->setupUi(this);
 //   setWindowFlags(Qt::FramelessWindowHint);
 //   setAttribute(Qt::WA_TranslucentBackground);
//    setObjectName("msgbox");
setWindowTitle(strTitle);
    //ui->label->setText(strTitle);
    ui->labelText->setText(strContent);
    //ui->toolButton->hide();
	if (leftBtnText.isEmpty())
	{
		showLeftBtn(false);
	}
	else
	{
		ui->btnCancel->setText(leftBtnText);
	}
	if (rightBtnText.isEmpty())
	{
		ui->btnOK->setVisible(false);
	}
	else
	{
		ui->btnOK->setText(rightBtnText);
	}
//    if(showCloseBtn){
//        ui->toolButton->show();
//    }else{
//       ui->toolButton->hide();
//    }
    int wd = parent->width() / 2 - this->width() / 2;
    int ht = parent->height() / 2 - this->height() / 2;
    this->move(parent->x()+wd, parent->y() + ht);
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(slotCancelClicked()));
    connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(slotOkClicked()));
     //connect(I18N::GetInstance(), SIGNAL(languageChanged()), this, SLOT(slot_languageChanged()));
}

CLMessageBox::CLMessageBox(QWidget *parent, const QString &title, const QString &text
                           , QMessageBox::StandardButtons buttons
                           , QMessageBox::StandardButton defaultButton)
    : QDialog(parent)
{
    m_pButtonBox = new QDialogButtonBox(this);
    m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    setDefaultButton(defaultButton);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_ShowModal, true);
    //ui->toolButton->hide();
    connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));


}

CLMessageBox::~CLMessageBox()
{
    delete ui;
}

void CLMessageBox::init()
{

}

QAbstractButton *CLMessageBox::clickedButton() const
{
    return m_pClickedButton;
}

QMessageBox::StandardButton CLMessageBox::standardButton(QAbstractButton *button) const
{
    return (QMessageBox::StandardButton)m_pButtonBox->standardButton(button);
}

void CLMessageBox::setDefaultButton(QPushButton *button)
{
    if (!m_pButtonBox->buttons().contains(button))
    {
        return;
    }
    m_pDefaultButton = button;
    button->setDefault(true);
    button->setFocus();
}

void CLMessageBox::setDefaultButton(QMessageBox::StandardButton button)
{
    setDefaultButton(m_pButtonBox->button(QDialogButtonBox::StandardButton(button)));
}

QMessageBox::StandardButton CLMessageBox::showWarning(QWidget *parent, const QString &title
                                                      , const QString &text
                                                      , QMessageBox::StandardButtons buttons
                                                      , QMessageBox::StandardButton defaultButton)
{
    CLMessageBox msgBox(parent, title, text, buttons, defaultButton);
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(m_pClickedButton);
}


E_MideaBtn CLMessageBox::warning(QWidget *parent, QString strTitle, QString strContent, QString leftBtnText, QString rightBtnText,  bool showCloseBtn)
{
    CLMessageBox msgBox(strTitle, strContent, leftBtnText, rightBtnText, parent, showCloseBtn);

    // 获取qt自带风格的Warning图片
    QPixmap pix = QMessageBox::standardIcon(QMessageBox::Warning);
    msgBox.setWindowIcon(QIcon(pix));

    if (msgBox.exec() == -1)
    {
        return EM_Cancel;
    }

    return msgBox.clickedBtn();
}

void CLMessageBox::setContent(const QString &strContent)
{
    ui->labelText->setText(strContent);
}

void CLMessageBox::showLeftBtn(bool isShowLeftBtn)
{
    ui->btnCancel->setVisible(isShowLeftBtn);
}

void CLMessageBox::show()
{
    if(this->parentWidget() != nullptr)
    {
        move((this->parentWidget()->width()-this->width())*0.5,
                           (this->parentWidget()->height()-this->height())*0.5);
    }

    QDialog::show();
}

void CLMessageBox::onButtonClicked(QAbstractButton *button)
{
    m_pClickedButton = button;
    done(execReturnCode(button));
}


int CLMessageBox::execReturnCode(QAbstractButton *button)
{
    int nResult = m_pButtonBox->standardButton(button);
    return nResult;
}

void CLMessageBox::slotOkClicked()
{
    m_eMideaBtn = EM_Ok;
    emit okSignal();
    close();
}

void CLMessageBox::slotCancelClicked()
{
    m_eMideaBtn = EM_Cancel;
    emit cancelSignal();
    close();
}

void CLMessageBox::slot_languageChanged()
{
    ui->retranslateUi(this);
    TIPSTR  = QObject::tr("");
    LEFTSTR = QObject::tr("取消");
    RIGHTSTR = QObject::tr("确定");
}


void CLMessageBox::on_toolButton_clicked()
{
    m_eMideaBtn = EM_Ok;
    emit cancelSignal();
    close();
}
