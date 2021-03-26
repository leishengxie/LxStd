
#include "LButtonGroup.h"
#include <QPainter>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>

CLButtonGroup::CLButtonGroup(QWidget *parent)
	: QWidget(parent)
	, m_btnPosition(0)
	, m_curIndex(0)
	, m_preIndex(0)
	, m_offset(0)
	, m_lineHeight(4)
	, m_lineColor(QColor(21, 156, 119))
    , m_spacing(25)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	m_btnGroup = new QButtonGroup(this);
	connect(m_btnGroup, SIGNAL(buttonClicked(int)), SLOT(onbuttonClicked(int)));

	m_animation = new QPropertyAnimation(this, "");
	m_animation->setDuration(200);
	connect(m_animation, SIGNAL(valueChanged(QVariant)), SLOT(onvalueChanged(QVariant)));

	//默认在上边
	setButtonPosition(South);

	m_uploadCount = 0; /// 上传数量
	m_downloadCount = 0; /// 下载数量
}

CLButtonGroup::~CLButtonGroup()
{

}

void CLButtonGroup::onvalueChanged(const QVariant &value)
{
    m_offset = value.toInt();
    update();
}

void CLButtonGroup::setLineHeight(int lineHeight)
{
    m_lineHeight = lineHeight;
}

void CLButtonGroup::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_lineColor);


    if (m_btnPosition == North)
    {
        painter.drawRect(m_offset, 0, m_btnSize.width(), m_lineHeight);
    }
    else if (m_btnPosition == South)
    {
        int spacing = m_curIndex*m_spacing;

        QPainterPath path;
        path.moveTo(m_offset+spacing+4,this->height() - m_lineHeight);
        path.lineTo(m_offset+m_btnSize.width()+spacing-4,this->height() - m_lineHeight);
        path.lineTo(m_offset+m_btnSize.width()+spacing,this->height());
        path.lineTo(m_offset+spacing,this->height());
        path.moveTo(m_offset+spacing+4,this->height() - m_lineHeight);


        painter.fillPath(path,m_lineColor);
//        painter.drawRect(m_offset, this->height() - m_lineHeight, m_btnSize.width(), m_lineHeight);
    }
    else if (m_btnPosition == West)
    {
        painter.drawRect(0, m_offset, m_lineHeight, m_btnSize.height());
    }
    else if (m_btnPosition == East)
    {
        painter.drawRect(this->width() - m_lineHeight, m_offset, m_lineHeight, m_btnSize.height());
    }

	//传输列表右上角红圈
	int count = m_uploadCount + m_downloadCount;
	if (count > 0)
	{
		//设置字体、大小、字符间距等
		QFont font;
		font.setPointSize(8);
		painter.setFont(font);
		

		QRect rt = rect();
		QRect rt1 = QRect(m_btnSize.width() * 2 + m_spacing, rt.top() + 15, 17, 17);
		painter.setPen(Qt::red);
		painter.setBrush(QBrush(Qt::red));
		painter.drawEllipse(rt1);
		painter.setPen(Qt::white);
		if (count > 99)
			count = 99;
		painter.drawText(rt1, Qt::AlignCenter, QString::number(count));
	}
}


QButtonGroup *CLButtonGroup::btnGroup() const
{
    return m_btnGroup;
}


void CLButtonGroup::setUploadCount(int count)
{
	if (m_uploadCount != count)
	{
		m_uploadCount = count;
		update();
	}
}

void CLButtonGroup::setDownloadCount(int count)
{
	if (m_downloadCount != count)
	{
		m_downloadCount = count;
		update();
	}
}

void CLButtonGroup::setButtonPosition(int position)
{
    deleteLayout();
    m_btnPosition = position;
    if (position == North)
    {
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, m_lineHeight, 0, 0);
        layout->setSpacing(m_spacing);
        setLayout(layout);
    }
    else if (position == South)
    {
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, m_lineHeight);
        layout->setSpacing(m_spacing);
        setLayout(layout);
    }
    else if (position == West)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setContentsMargins(m_lineHeight, 0, 0, 0);
        layout->setSpacing(m_spacing);
        setLayout(layout);
    }
    else if (position == East)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, m_lineHeight, 0);
        layout->setSpacing(m_spacing);
        setLayout(layout);
    }
    else
    {
        Q_ASSERT(false && "no match position!");
    }
}

void CLButtonGroup::addButton(QPushButton* btn, int id)
{
//    QPalette pa;
//    pa.setColor(QPalette::ButtonText,Qt::white);
//    btn->setPalette(pa);
//    QColor colorBtn(43,60,90);
    m_btnGroup->addButton(btn, id);
    m_buttonLst.append(btn);
    layout()->setSpacing(m_spacing);
    layout()->addWidget(btn);
    m_btnSize = btn->size();

    //btn->setStyleSheet("QPushButton{background-color:rgb(43,60,90)}");
//    btn->setStyleSheet("QPushButton{border-image: url(:/img/btn_style_normal.png);}"
//                  "QPushButton:hover{border-image: url(:/img/btn_style_v.png);color: rgb(0, 255, 127);}"
//                  "QPushButton:pressed{border-image: url(:/img/btn_style_down.png);}");

//    QString style = QString("QPushButton{background-color:#ffffff;border:none;}"
//        "QPushButton:hover{background-color:rgba(%1, %2, %3, 40);}"
//        "QPushButton:pressed, QPushButton:checked{background-color:rgba(%1, %2, %3, 80);}")
//            .arg(m_lineColor.red()).arg(m_lineColor.green()).arg(m_lineColor.blue());

    //QString style = QString("QPushButton{color:rgba(255, 255, 245,150);border:none;font-size:12px;}"
   //     "QPushButton:hover{color:rgba(255, 255, 255, 255);}"
   //     "QPushButton:pressed, QPushButton:checked{color:rgba(255, 255, 255, 255);}");

  //  btn->setStyleSheet(style);

      setBtStyle(0);

}
void CLButtonGroup::setBtStyle(int choiceIndex){
    QString qssNorm=QString("QPushButton{color:rgba(255, 255, 245,150);border:none;font-size:16px;}"
                              "QPushButton:hover{color:rgba(255, 255, 255, 255);}"
                              "QPushButton:pressed, QPushButton:checked{color:rgba(255, 255, 255, 255);}");
    QString qssChoice=QString("QPushButton{color:rgba(255, 255, 255,255);border:none;font-size:16px;}"
                              "QPushButton:hover{color:rgba(255, 255, 255, 255);}"
                              "QPushButton:pressed, QPushButton:checked{color:rgba(255, 255, 255, 255);}");
     int btCount=m_btnGroup->buttons().count();
     for(int i=0;i<btCount;i++){
         if(i!=choiceIndex){
             m_btnGroup->button(i)->setStyleSheet(qssNorm);
         }else{
             m_btnGroup->button(i)->setStyleSheet(qssChoice);
         }
     }
}

void CLButtonGroup::setLineColor(QColor color)
{
    m_lineColor = color;
}

void CLButtonGroup::onbuttonClicked(int index, bool bSend)
{
    //qDebug() << "..........index=" << index;
    if (bSend)
    {
        emit buttonClicked(index);
    }
    m_btnGroup->button(index)->setChecked(true);
    m_preIndex = m_curIndex;
    m_curIndex = index;
    if (m_btnPosition == North || m_btnPosition == South)
    {
        m_animation->setStartValue(m_preIndex * m_btnSize.width());
        m_animation->setEndValue(index * m_btnSize.width());
    }
    else if (m_btnPosition == West || m_btnPosition == East)
    {
        m_animation->setStartValue(m_preIndex * m_btnSize.height());
        m_animation->setEndValue(index * m_btnSize.height());
    }
    m_animation->start();
    setBtStyle(index);
}

void CLButtonGroup::deleteLayout()
{
    //清除布局，包括布局内控件
    if (this->layout() != nullptr)
    {
        QLayoutItem *child;
        while ((child = this->layout()->takeAt(0)) != 0) {
            delete child->widget();
            delete child;
            child = nullptr;
        }
        m_buttonLst.clear();
        delete this->layout();
        this->setLayout(nullptr);
    }
}

