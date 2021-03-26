#ifndef CUSTOMMAINWIDGET_H
#define CUSTOMMAINWIDGET_H

#include <QWidget>
#include "widgets/NoTitleMenuMainWidget.h"

namespace Ui {
class CCustomMainWidget;
}

class CCustomMainWidget : public CNoTitleMenuMainWidget
{
    Q_OBJECT

public:
    explicit CCustomMainWidget(QWidget *parent = 0);
    ~CCustomMainWidget();

private:
    Ui::CCustomMainWidget *ui;
};

#endif // CUSTOMMAINWIDGET_H
