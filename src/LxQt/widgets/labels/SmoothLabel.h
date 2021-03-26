#ifndef CSMOOTHLABEL_H
#define CSMOOTHLABEL_H

#include <QLabel>
class QPaintEvent;

class CSmoothLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CSmoothLabel(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CSMOOTHLABEL_H
