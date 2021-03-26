#include "LSearchEdit.h"
#include <QEvent>
#include <QApplication>
#include <QCompleter>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrameV2>
#include <QDebug>
#include <math.h>


static const int SIDE_MAGNIFYING_GLASS = 20;
CLMagnifyingGlass::CLMagnifyingGlass(QWidget *parent)
    : QWidget(parent)
{

}

void CLMagnifyingGlass::paintEvent(QPaintEvent *event)
{
    int nSide = width();
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);//设置反走样
    QPen pen(Qt::black, 2);//设置画笔
    //QPen pen(palette().highlight().color());//设置画笔
    painter.setPen(pen);

    int nBarWidth =  nSide * 0.4;
    int nBarHeight = nSide * 0.1;
    int r = nSide * 0.3;
    painter.save();//先画放大镜的那个把儿
    painter.setBrush(QBrush(QColor(0, 0, 0)));
    painter.translate(r, r);
    painter.rotate(45);
    painter.drawRect(r / std::sin(45 * 3.14 / 180 ), - nBarHeight * 0.5, nBarWidth, nBarHeight);
    painter.restore();
    // 弧度=角度*Pi/180, std::sin操作的是弧度而不是角度
    painter.translate(r, r);
    painter.drawEllipse( -r * std::sin(45 * 3.14 / 180 ), -r * std::sin(45 * 3.14 / 180), r * 2, r * 2); //画出我们想要的放大部分
}

QSize CLMagnifyingGlass::sizeHint() const
{
    return QSize(SIDE_MAGNIFYING_GLASS, SIDE_MAGNIFYING_GLASS);
}

void CLMagnifyingGlass::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    emit clicked();
}




#define SPACE_WIDGET        5

///
/// \brief CLSearchEditBase::CLSearchEditBase
/// \param parent
///
CLSearchEditBase::CLSearchEditBase(QWidget* parent)
    : QWidget(parent)
    , m_wgtShearch(NULL)
    , m_lineEdit(new QLineEdit(this))
{
    setFocusPolicy(m_lineEdit->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
    setSizePolicy(m_lineEdit->sizePolicy());
    setBackgroundRole(m_lineEdit->backgroundRole());

    setMouseTracking(true);
    setAcceptDrops(true);
    setAttribute(Qt::WA_MacShowFocusRect, true);
    QPalette p = m_lineEdit->palette();
    setPalette(p);

    // line edit
    // 去掉边框
    m_lineEdit->setFrame(false);
    m_lineEdit->setFocusProxy(this);
    m_lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);

    QPalette clearPalette = m_lineEdit->palette();
    clearPalette.setBrush(QPalette::Base, QBrush(Qt::transparent));
    m_lineEdit->setPalette(clearPalette);

    // 20191226 leisx
    m_lineEdit->setClearButtonEnabled(true);
    m_lineEdit->setPlaceholderText("请输入需要搜索的关键字!");
}



void CLSearchEditBase::setShearchWidget(QWidget* widget)
{
    m_wgtShearch = widget;
    updateGeometries();
}

QWidget* CLSearchEditBase::shearchWidget() const
{
    return m_wgtShearch;
}

void CLSearchEditBase::resizeEvent(QResizeEvent* event)
{
    updateGeometries();
    QWidget::resizeEvent(event);
}

void CLSearchEditBase::updateGeometries()
{
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    QRect rectSub = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);

    int nSubHeight = rectSub.height();
    int nSubWidth = rectSub.width();

    int nLineEditWidth = nSubWidth - m_wgtShearch->width() - SPACE_WIDGET * 2;
    int nLineEditHeight = nSubHeight;
    m_lineEdit->setGeometry(rectSub.x()
                            , rectSub.y() + (nSubHeight - nLineEditHeight) / 2
                            , nLineEditWidth
                            , nLineEditHeight);


    m_wgtShearch->setGeometry(m_lineEdit->rect().right() + SPACE_WIDGET
                              , rectSub.y() + (nSubHeight - m_wgtShearch->height()) / 2
                              , m_wgtShearch->width()
                              , m_wgtShearch->height());

}

void CLSearchEditBase::initStyleOption(QStyleOptionFrameV2* option) const
{
    option->initFrom(this);
    option->rect = contentsRect();
    option->lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, option, this);
    option->midLineWidth = 0;
    option->state |= QStyle::State_Sunken;
    if (m_lineEdit->isReadOnly())
    {
        option->state |= QStyle::State_ReadOnly;
    }
#ifdef QT_KEYPAD_NAVIGATION
    if (hasEditFocus())
    {
        option->state |= QStyle::State_HasEditFocus;
    }
#endif
    option->features = QStyleOptionFrameV2::None;
}

QSize CLSearchEditBase::sizeHint() const
{
    m_lineEdit->setFrame(true);
    QSize size = m_lineEdit->sizeHint();
    m_lineEdit->setFrame(false);
    return size;
}

void CLSearchEditBase::focusInEvent(QFocusEvent* event)
{
    m_lineEdit->event(event);
    QWidget::focusInEvent(event);
}

void CLSearchEditBase::focusOutEvent(QFocusEvent* event)
{
    m_lineEdit->event(event);

    if (m_lineEdit->completer())
    {
        connect(m_lineEdit->completer(), SIGNAL(activated(QString)),
                m_lineEdit, SLOT(setText(QString)));
    }
    QWidget::focusOutEvent(event);
}

void CLSearchEditBase::keyPressEvent(QKeyEvent* event)
{
    m_lineEdit->event(event);
}

bool CLSearchEditBase::event(QEvent* event)
{
    if (event->type() == QEvent::ShortcutOverride)
    {
        return m_lineEdit->event(event);
    }
    return QWidget::event(event);
}

void CLSearchEditBase::paintEvent(QPaintEvent* e)
{
    //如果从QWidget子类化一个Widget，为了能够使用样式表则需要为自定义Widget提供paintEvent事件。
    QPainter p(this);
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    style()->drawPrimitive(QStyle::PE_PanelLineEdit, &panel, &p, this);
    //return QWidget::paintEvent(e);
}

QVariant CLSearchEditBase::inputMethodQuery(Qt::InputMethodQuery property) const
{
    return m_lineEdit->inputMethodQuery(property);
}

void CLSearchEditBase::inputMethodEvent(QInputMethodEvent* e)
{
    m_lineEdit->event(e);
}



///
/// \brief CLSearchEdit::CLSearchEdit
/// \param parent
///
CLSearchEdit::CLSearchEdit(QWidget* parent)
    : CLSearchEditBase(parent)
{

    m_pMagnifyingGlass = new CLMagnifyingGlass(this);
    connect(m_pMagnifyingGlass, SIGNAL(clicked()), this, SLOT(onMagnifyingGlassClicked()));
    m_pMagnifyingGlass->setFixedSize(m_pMagnifyingGlass->sizeHint());
    m_pMagnifyingGlass->hide();
    setShearchWidget(m_pMagnifyingGlass);


    m_defaultBaseColor = palette().color(QPalette::Base);
    connect(m_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));

}

QLinearGradient CLSearchEdit::generateGradient(const QColor & color) const
{
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, m_defaultBaseColor);
    gradient.setColorAt(0.15, color.lighter(120));
    gradient.setColorAt(0.5, color);
    gradient.setColorAt(0.85, color.lighter(120));
    gradient.setColorAt(1, m_defaultBaseColor);
    return gradient;
}

void CLSearchEdit::paintEvent(QPaintEvent* event)
{
    QPalette p = palette();
    if (!m_lineEdit->text().isEmpty())
    {
        QColor lightYellow(248, 248, 210);
        p.setBrush(QPalette::Base, generateGradient(lightYellow));
    }
    else
    {
        p.setBrush(QPalette::Base, m_defaultBaseColor);
    }
    setPalette(p);
    CLSearchEditBase::paintEvent(event);
}


void CLSearchEdit::onMagnifyingGlassClicked()
{
    QString text = m_lineEdit->text();
    emit search(text);
    qDebug() << text;
}

void CLSearchEdit::onTextChanged(QString strText)
{
    m_pMagnifyingGlass->setVisible(!strText.isEmpty());
}


