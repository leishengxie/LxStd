#include "LTcpThread.h"
#include "LTcpServer.h"

//总结:

//继承QThread老式方法

//1.定义继承QThread的类A 复写run()函数;

//2.在主线程中实例化A对象a

//3.通过调用a->start()启动线程,线程会自动调用run()虚函数;run不可直接调用;

//新方法:

//1.创建继承Obeject的类A 将要在线程中实现的方法在A类中实现

//2.在主线程中实例化A对象a,再实例化QThread类对象b

//3.通过a.moveToThread(&b);将a对象的实现移入线程b对象作用范围内运行

//4.b->start()启动线程;

//5.通过信号与槽的方式启动调用A类成员函数;

//常用函数:

//QThread类

//start(),//启动线程;

//wait()//等待线程运行结束;

//quit(),//线程运行结束退出线程

LTcpThread::LTcpThread(QObject *parent)
    : QThread(parent)
{
    m_pLTcpServer = new LTcpServer(this);

    qDebug() << QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId());
}

LTcpThread::~LTcpThread()
{
    m_pLTcpServer->close();
    m_pLTcpServer->deleteLater();
}

// QThread只有run函数是在新线程里的
//在QThread中定义的所有东西都属于创建该QThread的线程。所以在构造函数中初始化的m_pLTcpServer应该是属于父线程的，
//那么在run中调用时就属于新线程调用。
void LTcpThread::run()
{
    exec();
}




