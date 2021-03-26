#include "CustomMainWidget.h"
#include "ui_CustomMainWidget.h"

CCustomMainWidget::CCustomMainWidget(QWidget *parent) :
    CNoTitleMenuMainWidget(parent),
    ui(new Ui::CCustomMainWidget)
{
    ui->setupUi(this);
}

CCustomMainWidget::~CCustomMainWidget()
{
    delete ui;
}
