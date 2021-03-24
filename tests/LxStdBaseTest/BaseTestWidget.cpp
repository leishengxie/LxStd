#include "BaseTestWidget.h"
#include "ui_BaseTestWidgetget.h"

CBaseTestWidget::CBaseTestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CBaseTestWidget)
{
    ui->setupUi(this);
}

CBaseTestWidget::~CBaseTestWidget()
{
    delete ui;
}

