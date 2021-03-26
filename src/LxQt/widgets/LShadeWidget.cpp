#include "LShadeWidget.h"


CLShadeLayer::CLShadeLayer(QWidget *parent)
: QWidget(parent)
{
    // 设置以单独窗口显示
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QPalette pa = palette();
    pa.setBrush(QPalette::Background, QColor(0, 0, 0));
    setPalette(pa);
    setWindowOpacity(0.5);
    setAttribute(Qt::WA_ShowModal, true);
}

void CLShadeLayer::showEvent(QShowEvent *event)
{
    QWidget* pMainWidget= parentWidget();
    if (pMainWidget != 0)
    {
        setGeometry(pMainWidget->geometry());
    }
}




///
/// \brief CLShadeWidget::CLShadeWidget
/// \param parent
///
CLShadeWidget::CLShadeWidget(QWidget *parent)
    : QWidget(parent)
    , m_pShadeLayer(new CLShadeLayer(parent))
{
    setWindowFlags(Qt::Window);
    setAttribute(Qt::WA_ShowModal, true);

}

void CLShadeWidget::showEvent(QShowEvent *envent)
{
    m_pShadeLayer->show();
}

void CLShadeWidget::hideEvent(QHideEvent *event)
{
    m_pShadeLayer->hide();
}

