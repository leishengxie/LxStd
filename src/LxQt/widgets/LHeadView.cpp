#include "LHeadView.h"
#define RECT_BOX_WIDTH              20
#define RECT_BOX_HEIGHT             20

CLHeadView::CLHeadView(Qt::Orientation orientation, QWidget *parent)
       : QHeaderView(orientation, parent)
       , m_bChecked(false)
{
       m_ptMouse.setX(100);
       m_ptMouse.setY(100);
}



/*绘制表头logicalIndex表示表头第几列，0表示第0列，也就是我们要画复选框的列，rect是表头第一列的大小*/
void CLHeadView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
       painter->save();
       QHeaderView::paintSection(painter, rect, logicalIndex);
       painter->restore();
       if (logicalIndex == 0)//第一列
       {
              //保存第一列的位置
              m_rectHeaderCheckBox.setX(rect.x() + rect.width() / 2 - RECT_BOX_WIDTH / 2);
              m_rectHeaderCheckBox.setY(rect.y() + rect.height() / 2 - RECT_BOX_HEIGHT / 2);
              m_rectHeaderCheckBox.setWidth(RECT_BOX_WIDTH);
              m_rectHeaderCheckBox.setHeight(RECT_BOX_HEIGHT);
              QStyleOptionButton option;
              //QPixmap pix;
              if (m_bChecked)
              {//图片需要在资源里添加
                     //pix.load(":/checkImage/image/checkImage/check-sel.png");//选中
                     option.state = QStyle::State_On;
              }
              else if (m_rectHeaderCheckBox.contains(m_ptMouse))
              {
                     //pix.load(":/checkImage/image/checkImage/check-hov.png");//高亮
                     option.state = QStyle::State_HasFocus;
              }
              else
              {
                     //pix.load(":/checkImage/image/checkImage/check-nor.png");//正常
                     option.state = QStyle::State_Off;
              }

              //style()->drawItemPixmap(painter, rect, Qt::AlignLeft | Qt::AlignVCenter, pix);


              //方法2，画选择按钮,，无法设置背景图片
              //
              option.rect = m_rectHeaderCheckBox;
              //QIcon icon(pix);
              //option.icon = icon;//setStyleSheet("background");
              style()->drawControl(QStyle::CE_CheckBox, &option, painter);

       }

}



void CLHeadView::mousePressEvent(QMouseEvent *event)
{
      if (isEnabled() && logicalIndexAt(event->pos()) == 0 && m_rectHeaderCheckBox.contains(event->pos() ))
       {
              m_bChecked = !m_bChecked;
              updateSection(0);//刷新表头第一列
              emit headCheckBoxToggled(m_bChecked);
       }
       else QHeaderView::mousePressEvent(event);
}

void CLHeadView::mouseMoveEvent(QMouseEvent *event)
{
       m_ptMouse = event->pos();
       if (m_rectHeaderCheckBox.contains(m_ptMouse))
       {
              updateSection(0);
       }
        QHeaderView::mouseMoveEvent(event);
}
