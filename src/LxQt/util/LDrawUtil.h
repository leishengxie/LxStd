#ifndef CLDRAWUTIL_H
#define CLDRAWUTIL_H

#include <QObject>

///
/// \brief The CLDrawUtil class     qt部分绘制方法
///
class CLDrawUtil : public QObject
{
    Q_OBJECT
public:
    explicit CLDrawUtil(QObject *parent = 0);

    //static void drawLoop(int nInnerRadii, nOuterRadii, const QColor & colorPen, const QColor & colorBrush, QPainter painter);

//    painter.save();
//    --radius;
//    painter.setPen(QColor(217, 221, 224));
//    painter.setBrush(QColor(217, 221, 224));

//    QPainterPath bigCircle;
//    bigCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);

//    radius -= 5;
//    QPainterPath smallCircle;
//    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);

//    QPainterPath path = bigCircle - smallCircle;
//    painter.drawPath(path);

//    painter.restore();
signals:

public slots:
};

#endif // CLDRAWUTIL_H
