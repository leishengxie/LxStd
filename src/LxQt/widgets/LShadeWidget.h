#ifndef CLSHADEWIDGET_H
#define CLSHADEWIDGET_H

#include <QWidget>

///
/// \brief The CLShadeLayer class 遮罩层
///
class CLShadeLayer : public QWidget
{
    Q_OBJECT
public:
    explicit CLShadeLayer(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *event);
};


///
/// \brief The CLShadeWidget class
///
class CLShadeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLShadeWidget(QWidget *parent = 0);

public:

signals:

protected:
    void showEvent(QShowEvent *envent);
    void hideEvent(QHideEvent* event);


public slots:

private:
    CLShadeLayer* m_pShadeLayer;
};

#endif // CLSHADEWIDGET_H
