#include "mainwindow.h"
#include <QApplication>

///
/// \brief qMain 用于测试lib里面的控件
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
