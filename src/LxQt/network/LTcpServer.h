#ifndef L_TCP_SERVER_H
#define L_TCP_SERVER_H
#include <QTcpServer>

/********新方法-另开线程把内存移到新线程里***********/

class LTcpConnection;
//class QTcpSocket;
// QTcpServer,QThread都继承自QObject, 所以注意此多继承具有二义性.
class LTcpServer
        : public QTcpServer
{
    Q_OBJECT
public:

    explicit LTcpServer(QObject *parent = Q_NULLPTR);
    ~LTcpServer();

public slots:
    void doDisConnectClient(qintptr handle); //主动断开连接信号
    void sendData(unsigned int cmd, char* data, unsigned int unSize);
    void sendData(qintptr handle, unsigned int cmd, char* data, unsigned int unSize);

signals:
    void clientConnected(qintptr handle, QString ip, quint16 port, int connectNum);//发送新用户连接信息
    /**
     * @brief socket已断开连接
     *   若需要在socket后析构后进行操作的可连接此信号
     * @param 连接句柄
     */
    void clientDisconnected(qintptr);
    void recv(qintptr handle, unsigned int unCmd, const char* data);
    void recvFile(qintptr handle, unsigned int unCmd, QString strFileName, QByteArray byteFile);

protected slots:
    /**
     * @brief 客户端已断开槽
     *   此槽与客户端的已断开信号连接
     * @param handle
     */
    void slot_clientDisconnect();
    //void slot_recv(qintptr handle, unsigned int unCmd, const char* data);
protected:
    /**
     * @brief 重写-有连接到来
     *    连接到来不一定连接，会根据maxPendingConnections决定是否连接
     * @param handle 连接句柄
     */
    virtual void incomingConnection(qintptr handle);

private:
    QMap<qintptr, LTcpConnection*> m_mapConnection; ///所有连接的map

};
#endif // L_TCP_SERVER_H
