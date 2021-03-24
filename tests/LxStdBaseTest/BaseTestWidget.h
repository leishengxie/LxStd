#ifndef CBASETESTWIDGET_H
#define CBASETESTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CBaseTestWidget; }
QT_END_NAMESPACE

class CBaseTestWidget : public QWidget
{
    Q_OBJECT

public:
    CBaseTestWidget(QWidget *parent = nullptr);
    ~CBaseTestWidget();

private:
    Ui::CBaseTestWidget *ui;
};
#endif // CBASETESTWIDGET_H
