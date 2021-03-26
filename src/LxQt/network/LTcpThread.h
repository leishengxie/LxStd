#ifndef L_TCP_THREAD_H
#define L_TCP_THREAD_H
#include <QThread>

class LTcpServer;
class LTcpConnection;

/******此方法属于老方法，被弃用*******/

class LTcpThread : public QThread
{
    Q_OBJECT
public:
    LTcpThread(QObject *parent=0);
    ~LTcpThread();
    void run();

public:
    LTcpServer* ctpServer()
    {
        return m_pLTcpServer;
    }

private:
    LTcpServer* m_pLTcpServer;

};

#endif // L_TCP_THREAD_H
