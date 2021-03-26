#include "ClickLabel.h"

CClickLabel::CClickLabel(QWidget *parent)
    :QLabel(parent)
{

}

CClickLabel::CClickLabel(const QString &text, QWidget *parent,Qt::WindowFlags f)
    :QLabel(text, parent, f)
{

}

void CClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    emit clicked();

}
