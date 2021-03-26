#ifndef CLHEADVIEW_H
#define CLHEADVIEW_H
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>

using namespace std;

class CLHeadView : public QHeaderView
{
       Q_OBJECT

public:
       explicit CLHeadView(Qt::Orientation orientation, QWidget *parent = 0);

signals:
       void headCheckBoxToggled(bool checked);


protected:
       void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
       void mousePressEvent(QMouseEvent *event);
       void mouseMoveEvent(QMouseEvent *event);


private:
       bool m_bChecked;
       QPoint m_ptMouse;
       mutable QRect m_rectHeaderCheckBox;

};

#endif // CLHEADVIEW_H
