#ifndef CLBUTTONGROUP_H
#define CLBUTTONGROUP_H
#include <QWidget>

class QButtonGroup;
class QPropertyAnimation;
class QPushButton;

enum E_ButtonGroup
{
    North,
    South,
    West,
    East
};


class CLButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit CLButtonGroup(QWidget *parent = 0);
    ~CLButtonGroup();

    void setLineHeight(int lineHeight);
    void setButtonPosition(int position);
    void addButton(QPushButton* btn, int id);
    void setLineColor(QColor color);
    void deleteLayout();
    void setBtStyle(int choiceIndex);

    QButtonGroup *btnGroup() const;

	void setUploadCount(int count); /// 上传数量

	void setDownloadCount(int count); /// 下载数量


signals:
    void buttonClicked(int);
public slots:
    void onvalueChanged(const QVariant &value);
    void onbuttonClicked(int index, bool bSend = true);

protected:
    void paintEvent(QPaintEvent *event);

private:
   QButtonGroup* m_btnGroup;
    QPropertyAnimation* m_animation;
    int m_btnPosition;
   int m_curIndex;
    int m_preIndex;
    int m_offset;
    int m_lineHeight;
    QColor m_lineColor;
    QList<QPushButton*> m_buttonLst;
    QSize m_btnSize;
	int m_spacing; /// 按钮间距
    int m_uploadCount; /// 上传数量
    int m_downloadCount; /// 下载数量
};

#endif // CLBUTTONGROUP_H
