#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <vector>
#include <QMessageBox>


#include "CustomMainWidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//QMessageBox

    /************
     *
     * 需要验证的控件
     *
     */

    // test CLSliderButton
    ui->sliderButton->addItem("123123");
    ui->sliderButton->addItem("text");
    ui->sliderButton->addItem("dfdff");

    // test NoTitleMenuMainWidget
    //m_pCustomMainWidget = new CCustomMainWidget;
    //CCustomMainWidget.show();

    // test CLShadeWidget 遮罩

    // test CLSliderButton

    // test CCompleteLineEdit
    ui->completeLineEdit->setListWords({"hello", "about", "you", "youuuuu"});

    // 提升的部件
    ui->progressIndicator->startAnimation();
    //自定义的插件
    ui->progressIndicator_2->startAnimation();

    ui->loadingWidget->start();

    // Tomast控件

    //
    //ui->roundProgressBar->

}

MainWindow::~MainWindow()
{
    delete ui;
    //m_pCustomMainWidget->deleteLater();
}
