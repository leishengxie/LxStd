#ifndef CLSXRADIOBUTTON_H
#define CLSXRADIOBUTTON_H

#include <QWidget>

///
/// \brief The CLsxRadioButton class 外观
///
class CLsxRadioButton: public QWidget
{
    Q_OBJECT
public:
    enum E_Btn_Status
    {
        EB_Normal,
        EB_Hover,
        EB_Press
    };

    CLsxRadioButton(const QString text,QWidget *parent = 0);

    void setBtnStatus(E_Btn_Status eBtnStatus);

    E_Btn_Status getBtnStatus()
    {
        return m_eBtnStatus;
    }

    void setPress(bool bPress);
    void initColor();
    void setTextColor(QColor colorNomal, QColor colorHover, QColor colorPress);
    void setBgColor(QColor colorNomal, QColor colorHover, QColor colorPress);
    void setBgImg(QString strImgNormal = "", QString strImgHover = "", QString strImgPress = "");

    QString text()
    {
        return m_text;
    }

signals:
    void emitStatus(E_Btn_Status);
    void clicked();
    void clicked(CLsxRadioButton*);

protected:
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    //void mouseMoveEvent(QMouseEvent *e);//鼠标按下后移动
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QRect m_rect;
    QString m_text;
    E_Btn_Status m_eBtnStatus;
    bool m_bMousePress;
    QColor m_colorTextNomal, m_colorTextHover, m_colorTextPress;
    QColor m_colorBgNomal, m_colorBgHover, m_colorBgPress;
    QString m_strImgNormal, m_strImgHover, m_strImgPress;
};


#endif // CLSXRADIOBUTTON_H
