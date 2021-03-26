#ifndef CCLICKLABEL_H
#define CCLICKLABEL_H
#include <QLabel>

class CClickLabel:public QLabel
{
    Q_OBJECT
public:
    explicit CClickLabel(QWidget *parent=0);
    explicit CClickLabel(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);

signals:
    void clicked(void);
protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);

private:
};

#endif // CCLICKLABEL_H
