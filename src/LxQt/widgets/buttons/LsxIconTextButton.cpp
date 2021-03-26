#include "LsxIconTextButton.h"

CLsxIconTextButton::CLsxIconTextButton(QWidget *parent)
    : CLsxButton(parent)
{

}

void CLsxIconTextButton::setEnabled(bool bEnabled)
{
    CLsxButton::setEnabled(bEnabled);
    //m_
}

void CLsxIconTextButton::init()
{

}

void CLsxIconTextButton::paintEvent(QPaintEvent *event)
{

}

void CLsxIconTextButton::enterEvent(QEvent *event)
{
    if (!isEnabled())
    {
        return;
    }
}

void CLsxIconTextButton::leaveEvent(QEvent *event)
{

}


