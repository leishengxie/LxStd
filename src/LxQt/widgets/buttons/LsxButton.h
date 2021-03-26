#ifndef CLSXBUTTON_H
#define CLSXBUTTON_H

#include <QWidget>

///
/// \brief The CLsxButton class 自定义的button
/// 所有Lsx开头的的button都继承QWidget
///
class CLsxButton: public QWidget
{
    Q_OBJECT
public:
    CLsxButton(QWidget *parent = 0);

    void setText(const QString & text)
    {
        m_text = text;
    }

signals:
    void clicked();


protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    //void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QRect m_rect;
    QString m_text;
    bool m_bPress;

};

#endif // CLSXBUTTON_H
