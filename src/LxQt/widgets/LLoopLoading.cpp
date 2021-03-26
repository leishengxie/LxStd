#include "LLoopLoading.h"
#include <QPainter>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QtDebug>

// 控件默认编程
static const int SIDE_SIZE = 120;

CLLoopLoading::CLLoopLoading(QWidget* parent)
    : QWidget(parent)
    , m_unAngle(0)
{

    if(!parent)
    {
        // 没有父对象不需要设置模态 Qt::WindowModal
        setWindowFlags(Qt::FramelessWindowHint
                       | Qt::WindowSystemMenuHint
                       | Qt::WindowMinMaxButtonsHint);
        setAttribute(Qt::WA_TranslucentBackground, true);
    }
//    else
//    {

//    }

    QFont font("Microsoft YaHei");
    font.setPixelSize(18);
    setFont(font);
    setFixedSize(sizeHint());

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(rotate()));
    m_timer->setInterval(30);



}

QSize CLLoopLoading::sizeHint() const
{
    return QSize(SIDE_SIZE, SIDE_SIZE);
}

void CLLoopLoading::start(const QString & strTip)
{
    show();
    m_timer->start();

}

void CLLoopLoading::stop()
{
    hide();
    m_timer->stop();
}

void CLLoopLoading::rotate()
{
    m_unAngle += 18;
    if (m_unAngle >= 360)
    {
        m_unAngle = 0;
    }
    update();
}

void CLLoopLoading::paintEvent(QPaintEvent* paintEvent)
{
    Q_UNUSED(paintEvent)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    qDebug() <<width() << height();

    int nFontHeight = painter.fontMetrics().height();
    int nSpace = 10;
    int side = qMin(height(), width()); // 时间width总大于height
    int nDiameters = side -  nFontHeight - nSpace;
    int radius = nDiameters / 2;
    painter.save();
    painter.translate(width() / 2, radius);
    --radius;

    /** 此方法最里面的区域无法透明
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    --radius;
    painter.setPen(QColor(217, 221, 224));
    painter.setBrush(QColor(217, 221, 224));
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    painter.setPen(QColor(55, 144, 206));
    painter.setBrush(QColor(55, 144, 206));
    int startAngle = m_unAngle * 16;
    int spanAngle = (m_unAngle + 45) * 16;
    painter.drawPie(-radius, -radius, radius * 2, radius * 2, startAngle, spanAngle);

    radius -= 5;
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    --radius;
    //    painter.save();
    //    painter.setCompositionMode( QPainter::CompositionMode_Clear );
    //    painter.drawEllipse(QPoint(0, 0), radius, radius);
    //QRegion::Ellipse

    QPainterPath painterPath;
    painterPath.addEllipse(QPoint(0, 0), radius, radius);
    //    painter.fillPath(painterPath, Qt::transparent);
    painter.fillPath(painterPath, QColor(0, 0, 0, 100));
    //    painter.restore();
    */

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    QRegion r1(-radius, -radius, radius * 2, radius * 2, QRegion::Ellipse);
    --radius;
    QRegion r2(-radius, -radius, radius * 2, radius * 2, QRegion::Ellipse);
    QRegion r = r1 - r2;
    painter.setClipRegion(r);
    painter.fillRect(r.boundingRect(), Qt::white);

    int radiusColor = radius - 5;
    painter.setPen(QColor(217, 221, 224));
    painter.setBrush(QColor(217, 221, 224));
    QRegion r3(-radiusColor, -radiusColor, radiusColor * 2, radiusColor * 2, QRegion::Ellipse);
    QRegion rr = r2 - r3;
    painter.setClipRegion(rr);
    painter.fillRect(rr.boundingRect(), QColor(217, 221, 224));

    painter.setPen(QColor(55, 144, 206));
    painter.setBrush(QColor(55, 144, 206));
    QPainterPath path;
    //path.arcMoveTo(-radius, -radius, radius * 2,radius * 2, m_unAngle);
    path.moveTo(0, 0);
    path.arcTo(-radius, -radius, radius * 2, radius * 2, 0, 45);

//     path.arcMoveTo(-radiusColor, -radiusColor, radiusColor * 2,radiusColor * 2, m_unAngle + 45);
//     path.arcTo(-radiusColor, -radiusColor, radiusColor * 2,radiusColor * 2, m_unAngle + 45, m_unAngle);
    painter.rotate(m_unAngle);    // 逆时针旋转 30 度
    painter.drawPath(path);

    radius = radiusColor - 1;
    QRegion r4(-radius, -radius, radius * 2, radius * 2, QRegion::Ellipse);
    QRegion rrr = r3 - r4;
    painter.setClipRegion(rrr);
    painter.fillRect(r.boundingRect(), Qt::white);

    painter.resetTransform();
    painter.restore();

    QTextOption option(Qt::AlignCenter);
    painter.drawText(QRect(0, height() - nFontHeight, width(), nFontHeight), m_strTip, option);

}

void CLLoopLoading::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    int nFontWidth = fontMetrics().width(m_strTip);
    int nWidthFix = qMax(nFontWidth, SIDE_SIZE);
    setFixedSize(nWidthFix, height());

    if (parentWidget())
    {
        move(parentWidget()->width() / 2 - width() / 2,
             parentWidget()->height() / 2 - height() / 2);
    }
    else
    {
        QRect screenRect = QGuiApplication::primaryScreen()->geometry();
        move(screenRect.width() / 2 - width() / 2,
             screenRect.height() / 2 - height() / 2);
    }

}
