
#include <QtCore/QTimer>
#include <QtCore/QString>
#include <QtCore/QPropertyAnimation>

#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QApplication>
#include <QMainWindow>
#include "LOperateTip.h"

extern QMainWindow * g_pMainWindow;

static const QString c_szStyleSheet = "QWidget{background-color:%1;\
									  border:1px solid %2;border-top:0;border-bottom-left-radius:3px;\
									  border-bottom-right-radius:3px;background-image: url();}\
									  ";

static const char *c_szGMPOperateTip = "GMPOperateTip";
static const char *c_szSuccess = QT_TRANSLATE_NOOP("GMPOperateTip", "操作成功");
static const char *c_szWaring = QT_TRANSLATE_NOOP("GMPOperateTip", "操作失败");

/*!
*@brief 淡出提示框
*@author Leisx 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void CLOperateTip::fadeOut(QWidget * parent, QString strText, const unsigned int nShowTime, const unsigned int nAnimationTime)
{
    CLOperateTip * tipWidget = new CLOperateTip(parent);
	tipWidget->setAnimationMode(AM_FADEOUT);
	tipWidget->setText(strText);
	tipWidget->setStayTime(nShowTime);
	tipWidget->setAnimationdDuration(nAnimationTime);
	tipWidget->show();
}

/*!
*@brief 自定义飞出方向提示框
*@author Leisx 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；direction：飞出方向；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void CLOperateTip::flyOut(QWidget * parent, QString strText, Direction direction, const unsigned int nShowTime,
                        const unsigned int nAnimationTime)
{
    CLOperateTip * tipWidget = new CLOperateTip(parent);
	tipWidget->setAnimationMode(AM_FLYOUT);
	tipWidget->setStyleSheet(c_szStyleSheet.arg("#12B33D").arg("#2ABB51"));
	tipWidget->setText(strText);
	tipWidget->setFlyoutDirection(direction);
	tipWidget->setStayTime(nShowTime);
	tipWidget->setAnimationdDuration(nAnimationTime);
	tipWidget->show();
}

/*!
*@brief 自定义背景色提示框
*@author Leisx 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；color：背景色；animation：动画模式；direction：飞出方向；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void CLOperateTip::colorize(QWidget * parent, QString strText, const QColor & color, AnimationMode animation,
                          Direction direction, const unsigned int nShowTime, const unsigned int nAnimationTime)
{
    CLOperateTip * tipWidget = new CLOperateTip(parent);
	tipWidget->setText(strText);
	tipWidget->setBackgroundColor(color);
	tipWidget->setAnimationMode(animation);
	tipWidget->setFlyoutDirection(direction);
	tipWidget->setStayTime(nShowTime);
	tipWidget->setAnimationdDuration(nAnimationTime);
	tipWidget->show();
}

/*!
*@brief 警告提示框
*@author Leisx 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void CLOperateTip::waring(QWidget * parent, QString strText, const unsigned int nShowTime, const unsigned int nAnimationTime)
{
    CLOperateTip * tipWidget = new CLOperateTip(parent);
	tipWidget->setAnimationMode(AM_FLYOUT);
	tipWidget->setFlyoutDirection(D_TOP);
    tipWidget->setIcon(":/Resources/image/warning.png");
	tipWidget->setStyleSheet(c_szStyleSheet.arg("#FF9830").arg("#FF9326"));
 	if (strText.isEmpty())
 	{
 		tipWidget->setText(qApp->translate(c_szGMPOperateTip, c_szWaring));
 	}
 	else
 	{
 		tipWidget->setText(strText);
 	}
	tipWidget->setStayTime(nShowTime);
	tipWidget->setAnimationdDuration(nAnimationTime);
	tipWidget->show();
}

/*!
*@brief 成功提示框
*@author Leisx 2017年8月7日
*@param[in]   parent：父窗口；strText：提示框内容；nShowTime：显示时长； nAnimationTime：消失动画时长
*@return       void
*/
void CLOperateTip::success(QWidget * parent, QString strText, const unsigned int nShowTime, const unsigned int nAnimationTime)
{
    CLOperateTip * tipWidget = new CLOperateTip(parent);
	tipWidget->setStyleSheet(c_szStyleSheet.arg("#12B33D").arg("#2ABB51"));
	tipWidget->setAnimationMode(AM_FLYOUT);
	tipWidget->setFlyoutDirection(D_TOP);
	if (strText.isEmpty())
	{
		tipWidget->setText(qApp->translate(c_szGMPOperateTip, c_szSuccess));
	}
	else
	{
		tipWidget->setText(strText);
	}
	tipWidget->setStayTime(nShowTime);
	tipWidget->setAnimationdDuration(nAnimationTime);

	tipWidget->show();
}

CLOperateTip::CLOperateTip(QWidget * parent)
	: QWidget(parent)
	, m_eMode(AM_FLYOUT)
	, m_eDirection(D_TOP)
	, m_DurationTime(500)
	, m_iStayDuration(4000)
    , m_pLabelIcon(nullptr)
    , m_pLabelText(nullptr)
	, m_pMoveWidget(nullptr)
    , m_pPropertyAnim(nullptr)
    , m_pOpacityEffect(nullptr)
    , m_pDropShadowEffect(nullptr)
{
    // 窗口关闭时删除
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose, false);

    initUI();
    initConnect();
	
	setShadowEnable(true);

	m_pMoveWidget->setMinimumWidth(130);

	m_StayTimer.setSingleShot(true);
}

CLOperateTip::~CLOperateTip()
{
    m_pLabelIcon = nullptr;
    m_pLabelText = nullptr;
	m_pMoveWidget = nullptr;
    m_pPropertyAnim = nullptr;
    m_pOpacityEffect = nullptr;
    m_pDropShadowEffect = nullptr;
}

// 设置文本内容
void CLOperateTip::setText(const QString & text)
{
    if (m_pLabelText)
	{
        m_pLabelText->setText(text);
	}
}

// 设置图标
void CLOperateTip::setIcon(const QString & icon)
{
    if (m_pLabelIcon)
	{
        m_pLabelIcon->setPixmap(QPixmap(icon));
	}
}

// 设置背景色
void CLOperateTip::setBackgroundColor(const QColor & color)
{
	QColor border = color;
	border.setAlpha(255 * 0.1);
	QString strBorderRgba = QString("rgba(%1,%2,%3,%4)").arg(border.red()).arg(border.green()).arg(border.blue()).arg(border.alpha());
	setStyleSheet(c_szStyleSheet.arg(color.name()).arg(strBorderRgba));
}

// 消失动画模式
void CLOperateTip::setAnimationMode(AnimationMode mode)
{
	if (m_eMode == mode)
	{
		return;	
	}

	m_eMode = mode;
}

// 消失动画为飞出时有效 设置飞出方向
void CLOperateTip::setFlyoutDirection(Direction direction)
{
	if (m_eDirection == direction)
	{
		return;	
	}

	m_eDirection = direction;
}

// 设置是否启用提示框阴影
void CLOperateTip::setShadowEnable(bool enable)
{
    if (!m_pDropShadowEffect)
	{
        m_pDropShadowEffect = new QGraphicsDropShadowEffect(this);
        m_pDropShadowEffect->setColor(QColor(0, 0, 0, 70)); // 设定阴影的颜色
        m_pDropShadowEffect->setBlurRadius(10);             // 设定阴影的模糊度
        m_pDropShadowEffect->setOffset(4, 4);               // 设定在哪个方向产生阴影效果，如果dx为负数，则阴影在图形元素的左边
	}

    setGraphicsEffect(enable ? m_pDropShadowEffect : nullptr);
}

// 设置提示框消失动画时长
void CLOperateTip::setAnimationdDuration(int duration)
{
	m_DurationTime = duration;
}

// 设置提示框停留时长
void CLOperateTip::setStayTime(int time)
{
	m_iStayDuration = time;
}

//  重写窗口事件函数，当窗口显示时启动定时器
bool CLOperateTip::event(QEvent * e)
{
	if (e->type() == QEvent::Show)
	{
		adjustSize();
		int nposx = qrand() % (parentWidget()->rect().width() - this->rect().width());
		int nposy = qrand() % (parentWidget()->rect().height() - this->rect().height() );

		move(nposx, nposy);

		m_StayTimer.start(m_iStayDuration);
	}

    //return __super::event(e); //cl 编译器
    return QWidget::event(e);
}

void CLOperateTip::paintEvent(QPaintEvent *)
{

}

// 提示框内部布局，可重写
void CLOperateTip::layoutIconAndLabel(QHBoxLayout * layout)
{
    m_pLabelIcon = new QLabel(this);
    QPixmap pixmap(":/Resources/image/success.png");
    m_pLabelIcon->setPixmap(pixmap);
    m_pLabelIcon->setStyleSheet("border:0px solid #FFFFFF;");

    m_pLabelText = new QLabel("", this);
    m_pLabelText->setStyleSheet("border:0px solid #FFFFFF;\
 							  color: #FFFFFF;\
 							  font-size: 14px;\
 							  font-family:'Microsoft YaHei';\
 							  ");

    layout->addWidget(m_pLabelIcon);
    layout->addWidget(m_pLabelText);
}

// 初始化住界面布局
void CLOperateTip::initUI()
{
    QHBoxLayout *hLay = new QHBoxLayout;
    hLay->setContentsMargins(10, 4, 11, 6);
    hLay->setSpacing(10);

    layoutIconAndLabel(hLay);

    QWidget * widgetBg = new QWidget;
    widgetBg->setLayout(hLay);

    QHBoxLayout * hLayMain = new QHBoxLayout;
    hLayMain->setSpacing(0);
    hLayMain->setMargin(0);

    hLayMain->addWidget(widgetBg);
    m_pMoveWidget = widgetBg;

    setLayout(hLayMain);
}

// 初始化动画，并添加定时器槽函数
void CLOperateTip::initConnect()
{
    m_pPropertyAnim = new QPropertyAnimation(this);
    m_pPropertyAnim->setTargetObject(this);

    connect(m_pPropertyAnim, &QPropertyAnimation::finished, this, &CLOperateTip::close);

	connect(&m_StayTimer, &QTimer::timeout, this, [this]{
        m_pPropertyAnim->setDuration(m_DurationTime);
		switch (m_eMode)
		{
		case AM_FADEOUT:
			fade();
			break;
		case AM_FLYOUT:
			moveOut();
			break;
		case AM_ZOOMIN:
			zoomIn();
			break;
		default:
			;
		}

        m_pPropertyAnim->start();
	});
}

// 提示框缩小动画
void CLOperateTip::zoomIn()
{
    m_pPropertyAnim->setPropertyName("geometry");

	QRect startRect = rect();
	startRect.moveTo(pos());
	QRect stopRect = QRect(startRect.center(), QSize(0, 0));

    m_pPropertyAnim->setStartValue(startRect);
    m_pPropertyAnim->setEndValue(stopRect);
}

// 提示框飞出动画
void CLOperateTip::moveOut()
{
    m_pPropertyAnim->setTargetObject(m_pMoveWidget);
    m_pPropertyAnim->setPropertyName("pos");

    m_pPropertyAnim->setStartValue(QPoint());
	switch (m_eDirection)
	{
	case D_LEFT:
        m_pPropertyAnim->setEndValue(QPoint(-width(), 0));
		break;
	case D_TOP:
        m_pPropertyAnim->setEndValue(QPoint(0, -height()));
		break;
	case D_RIGHT:
        m_pPropertyAnim->setEndValue(QPoint(width(), 0));
		break;
	case D_BOTTOM:
        m_pPropertyAnim->setEndValue(QPoint(0, height()));
		break;
	default:
		;
	}
}

// 提示框淡出动画
void CLOperateTip::fade()
{
    m_pOpacityEffect = new QGraphicsOpacityEffect(this);
    m_pOpacityEffect->setOpacity(1);

    setGraphicsEffect(m_pOpacityEffect);

    m_pPropertyAnim->setTargetObject(m_pOpacityEffect);
    m_pPropertyAnim->setPropertyName("opacity");

    m_pPropertyAnim->setStartValue(1);
    m_pPropertyAnim->setEndValue(0);
}


