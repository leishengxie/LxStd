#ifndef L_TCP_CONNECTION_H
#define L_TCP_CONNECTION_H
#include <QTcpSocket>

class LTcpConnection : public QTcpSocket
{
    Q_OBJECT
public:

    LTcpConnection(qintptr handle, QObject *parent = 0);

    qintptr handle()
    {
        return m_Handle;
    }

    void doDisconnectSocket(qintptr handle);

signals:
    //添加recv信号
    void recv(qintptr handle, unsigned int unCmd, const char* data);
    void recvFile(qintptr handle, unsigned int unCmd, QString strFileName, QByteArray byteFile);

public slots:


private slots:
    void readData();

private:
    qintptr m_Handle;//连接标识
    quint32 m_unBlockSize;
    int m_nCmd;
};


#endif // L_TCP_CONNECTION_H
