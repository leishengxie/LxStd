#ifndef CLSWITCHBUTTON_H
#define CLSWITCHBUTTON_H

#include <QWidget>

/**
 *
 * 1:可设置开关按钮的样式 圆角矩形/内圆形/外圆形/图片
 * 2:可设置选中和未选中时的背景颜色
 * 3:可设置选中和未选中时的滑块颜色
 * 4:可设置显示的文本
 * 5:可设置滑块离背景的间隔
 * 6:可设置圆角角度
 */


class QTimer;

///
/// \brief The CLSwitchButton class 开关按钮
///  如播放-暂停，开-关
///
class CLSwitchButton: public QWidget
{
    Q_OBJECT
        Q_PROPERTY(QString textOff READ getTextOff WRITE setTextOff)
        Q_PROPERTY(QString textOn READ getTextOn WRITE setTextOn)
        Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
        Q_PROPERTY(E_ButtonStyle buttonStyle READ getButtonStyle WRITE setButtonStyle)
public:
    // 定义按钮的风格
    enum E_ButtonStyle
    {
        EBS_Rect = 0,     //圆角矩形
        EBS_CircleIn = 1, //内圆形
        EBS_CircleOut = 2,//外圆形
        EBS_Image = 3     //图片
    };
    Q_ENUM(E_ButtonStyle)

//    enum E_ButtonStatus
//    {
//        EB_On,
//        EB_Off
//    };

    CLSwitchButton(QWidget* parent = 0);
    ~CLSwitchButton();

public:
    bool isChecked()const
    {
        return m_bChecked;
    }
    //设置是否选中
    void setChecked(bool bChecked);

    E_ButtonStyle getButtonStyle()const
    {
        return m_eButtonStyle;
    }
    //设置风格样式
    void setButtonStyle(E_ButtonStyle eButtonStyle);

    QColor getBgColorOff()const
    {
        return bgColorOff;
    }
    QColor getBgColorOn()const
    {
        return bgColorOn;
    }

    QColor getSliderColorOff()const
    {
        return sliderColorOff;
    }
    QColor getSliderColorOn()const
    {
        return sliderColorOn;
    }

    QColor getTextColorOff()const
    {
        return textColorOff;
    }
    QColor getTextColorOn()const
    {
        return textColorOn;
    }

    QString getTextOff()const
    {
        return m_strTextOff;
    }
    void setTextOff(QString strTextOff)
    {
        m_strTextOff = strTextOff;
        update();
    }

    QString getTextOn()const
    {
        return m_strTextOn;
    }
    void setTextOn(QString strTextOn)
    {
        m_strTextOn = strTextOn;
        update();
    }

    QString getImageOff()const
    {
        return imageOff;
    }
    QString getImageOn()const
    {
        return imageOn;
    }

    int getSpace()const
    {
        return space;
    }
    int getRectRadius()const
    {
        return rectRadius;
    }

public slots:




    //设置背景颜色
    void setBgColor(QColor bgColorOff, QColor bgColorOn);
    //设置滑块颜色
    void setSliderColor(QColor sliderColorOff, QColor sliderColorOn);
    //设置文本颜色
    void setTextColor(QColor textColorOff, QColor textColorOn);



    //设置背景图片
    void setImage(QString imageOff, QString imageOn);

    //设置间隔
    void setSpace(int space);
    //设置圆角角度
    void setRectRadius(int rectRadius);

signals:
    void checkedChanged(bool bChecked);

protected:
    void mousePressEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent*);
    void drawBg(QPainter* painter);
    void drawSlider(QPainter* painter);
    void drawText(QPainter* painter);
    void drawImage(QPainter* painter);

    virtual QSize sizeHint() const;


private slots:
    void updateValue();
    //void recalculateWidth();


private:
    bool m_bChecked;               //是否选中
    E_ButtonStyle m_eButtonStyle;    //开关按钮样式

    QColor bgColorOff;          //关闭时背景颜色
    QColor bgColorOn;           //打开时背景颜色

    QColor sliderColorOff;      //关闭时滑块颜色
    QColor sliderColorOn;       //打开时滑块颜色

    QColor textColorOff;        //关闭时文本颜色
    QColor textColorOn;         //打开时文本颜色

    QString m_strTextOff;            //关闭时显示的文字
    QString m_strTextOn;             //打开时显示的文字

    QString imageOff;           //关闭时显示的图片
    QString imageOn;            //打开时显示的图片

    int space;                  //滑块离背景间隔
    int rectRadius;             //圆角角度

    int step;                   //每次移动的步长
    int startX;                 //滑块开始X轴坐标
    int endX;                   //滑块结束X轴坐标
    QTimer* timer;              //定时器绘制
};
#endif // CLSWITCHBUTTON_H
