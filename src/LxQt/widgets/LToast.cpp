#include "LToast.h"
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>

CLToast::CLToast(QWidget* parent, const QString & message, int w, int h, const QString & style)
    : QLabel(parent)
{
    setText(message);
    setFixedSize(w, h);
    setAlignment(Qt::AlignCenter);
    if (parent)
    {
        startx = (parent->width() - width()) / 2;
        starty = parent->height();
        endy = parent->height() * 3 / 4;
    }
    else
    {
        setWindowFlags(Qt::FramelessWindowHint
                       | Qt::WindowSystemMenuHint
                       | Qt::WindowMinMaxButtonsHint);

        QScreen* screen = QGuiApplication::primaryScreen ();
        QRect mm = screen->availableGeometry() ;
        startx = (mm.width() - width()) / 2;
        starty = mm.height();
        endy = mm.height() * 3 / 4;
    }
    setStyleSheet(style);
    setShadow(this);
}

void CLToast::toastr()
{
    QPropertyAnimation* animal = new QPropertyAnimation(this, "pos");
    animal->setDuration(500);
    animal->setStartValue(QPoint(startx, starty));
    animal->setEndValue(QPoint(startx, endy));
    animal->setEasingCurve(QEasingCurve::OutCubic); // 按指定的曲线运动
//    下面有一些常用的曲线效果：
//    anim1->setEasingCurve(QEasingCurve::CosineCurve);  //余弦曲线
//    anim1->setEasingCurve(QEasingCurve::SineCurve);   //正弦曲线
//    anim1->setEasingCurve(QEasingCurve::InBack);   //回撤效果
//    anim1->setEasingCurve(QEasingCurve::InBounce); //回弹效果
    connect(animal, SIGNAL(finished()), this, SLOT(animationFinished()));
    this->show();
    animal->start();
}

void CLToast::showStr(QWidget* parent, const QString & strText)
{
    CLToast* pToast = new CLToast(parent, strText);
    pToast->toastr();
}

void CLToast::setShadow(QWidget* w, qreal blurRadius, qreal dx, qreal dy)
{
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(blurRadius);
    shadow->setColor(QColor(0, 0, 0, 160));
    shadow->setOffset(dx, dy);
    w->setGraphicsEffect(shadow);
}

void CLToast::animationFinished()
{
    QTimer::singleShot(400, this, SLOT(delSelf()));
}

void CLToast::delSelf()
{
    delete this;
}
