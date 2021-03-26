#ifndef CTHREEIMGPUSHBUTTON_H
#define CTHREEIMGPUSHBUTTON_H
#include <QPushButton>

///
/// \brief The CThreeImgPushButton class 是否继承QPushButton的style风格
///
class CThreeImgPushButton:public QPushButton
{
    Q_OBJECT
public:
   explicit CThreeImgPushButton(QWidget *parent = 0);
   explicit CThreeImgPushButton(const QString text,QWidget *parent = 0);
   ~CThreeImgPushButton();

   void setBgImg(QString strImgNormal, QString strImgHover, QString strImgPress);
   void enterEvent(QEvent *);//进入事件
   void leaveEvent(QEvent *);//离开事件
   void mousePressEvent(QMouseEvent *event);  //鼠标按下事件
   void mouseReleaseEvent(QMouseEvent *event); //鼠标释放事件
   void paintEvent(QPaintEvent *);//按钮绘图事件

private:
   enum ButtonStatus{NORMAL, HOVER, PRESS};	//枚举按钮的几种状态
   ButtonStatus status;
   bool mouse_press; //按钮左键是否按下
   QString m_strImgNormal, m_strImgHover, m_strImgPress;
};

#endif // CTHREEIMGPUSHBUTTON_H
