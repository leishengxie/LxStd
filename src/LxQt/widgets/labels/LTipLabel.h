#ifndef CLTIPLABEL_H
#define CLTIPLABEL_H

#include <QLabel>

class CLTipLabel: public QLabel
{
public:
    explicit CLTipLabel(QWidget *parent=0);
    explicit CLTipLabel(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    void setRealQString(QString strReal)
    {
        m_strReal = strReal;
    }

    QString strRecombineLine(const QString &strSrc);

private:
    QString m_strReal;

};

#endif // CLTIPLABEL_H
