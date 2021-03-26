#ifndef CMEDIAPUSHBUTTON_H
#define CMEDIAPUSHBUTTON_H

#include <QPushButton>

class QMediaPlayer;

///
/// \brief The CMediaPushButton class 声音按钮
///
class CMediaPushButton : public QPushButton
{
    Q_OBJECT
public:
    CMediaPushButton(const QString &text,QWidget *parent);
    CMediaPushButton(QWidget *parent=0);
    CMediaPushButton(const QString &text);

signals:

public slots:

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    void init();

private:
    QMediaPlayer *player;
    //QCursor *cursor;

};

#endif // CMEDIAPUSHBUTTON_H
