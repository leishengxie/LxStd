#ifndef CLHOVERLABEL_H
#define CLHOVERLABEL_H
#include <QLabel>

class CLHoverLabel: public QLabel
{
    Q_OBJECT
public:
    explicit CLHoverLabel(QWidget *parent=0);
    explicit CLHoverLabel(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    bool m_bEnter;
};

#endif // CLHOVERLABEL_H
