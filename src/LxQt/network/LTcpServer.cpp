#include "LTcpServer.h"
#include "LTcpConnection.h"
//#include "datastructure/LBuffer.h"
#include <QDataStream>

LTcpServer::LTcpServer(QObject *parent)
    : QTcpServer(parent)
{
    setMaxPendingConnections(1000);
    if(!listen(QHostAddress::Any, 6000))
    {
        qDebug()<<errorString();    //错误信息
        return;
    }
}

LTcpServer::~LTcpServer()
{
    for(LTcpConnection *client : m_mapConnection.values())
    {
        client->disconnectFromHost();
        auto handle = client->socketDescriptor();
        client->deleteLater();
        emit clientDisconnected(handle); //告知其他调用者 当前socket断开，避免有需要在socket后执行的方法
    }
    close();
}


void LTcpServer::doDisConnectClient(qintptr handle)
{

    QMap<qintptr, LTcpConnection*>::iterator it = m_mapConnection.find(handle);
    if (it != m_mapConnection.end())
    {
        m_mapConnection[handle]->doDisconnectSocket(handle);
    }

}

void LTcpServer::sendData(unsigned int cmd, char *data, unsigned int unSize)
{

}

void LTcpServer::sendData(qintptr handle, unsigned int cmd, char *data, unsigned int unSize)
{
    // 20200101 去掉自定义的CLBuffer， 改用qt的ByteArray
//    CLBuffer sendBuf;
//    sendBuf.WriteUInt32(0);
//    sendBuf.WriteUInt32(cmd);
//    sendBuf.Write((const unsigned char*)data, unSize);
//    int nSize = sendBuf.DataSize();
//    sendBuf.SetEndPos(0);
//    sendBuf.WriteUInt32(nSize); //2018-4-4,改为长度本身所占的字节也加上去
//    sendBuf.SetEndPos(nSize);
//    m_mapConnection[handle]->write((char *)sendBuf.Begin(), nSize);
//    m_mapConnection[handle]->waitForBytesWritten(300);

    QByteArray m_byteBlock;
    m_byteBlock.clear();
    QDataStream out(&m_byteBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);
    //    out << (quint16)0;
    //    out << (quint16)0;
    out << (quint32)0;
    out << cmd;
    m_byteBlock.append(data, unSize);
    int m_llBytesTotal = m_byteBlock.size();
    // 如果发2字节总长度out.device()->seek(2); out << (quint16)(byteBlock.size()-sizeof(quint16)*2);
    out.device()->seek(0);
    out << m_llBytesTotal; // 包含本身所占的4字节
    //m_llBytesToWrite = m_llBytesTotal - write(m_byteBlock);
        m_mapConnection[handle]->write(m_byteBlock);
        m_mapConnection[handle]->waitForBytesWritten(300);

}

//重写-有连接到来
void LTcpServer::incomingConnection(qintptr handle) {
    //超出最大练级数量关闭连接
    if (m_mapConnection.size() > maxPendingConnections())
    {
        QTcpSocket tcp;
        tcp.setSocketDescriptor(handle);
        tcp.disconnectFromHost();
        qDebug() << "maxPendingConnections()" << maxPendingConnections();
        return;
    }
    auto clientConnection = new LTcpConnection(handle, this);

    Q_ASSERT(clientConnection->socketDescriptor() == handle);
    //socket断开连接的信号与server槽连接
    //connect(this, &LTcpServer::doDisConnectClient, clientConnection, &LTcpConnection::DisconnectSocket);
    connect(clientConnection, SIGNAL(disconnected()), this, SLOT(slot_clientDisconnect()));
    connect(clientConnection, SIGNAL(recv(qintptr,uint,const char*)), this, SIGNAL(recv(qintptr,uint,const char*)));
    connect(clientConnection, SIGNAL(recvFile(qintptr,uint,QString,QByteArray)), this, SIGNAL(recvFile(qintptr,uint,QString,QByteArray)));
    //map记录
    m_mapConnection.insert(handle, clientConnection);
    //qDebug()<<"connected:" <<handle << clientConnection->peerAddress().toString() << clientConnection->peerPort() << "  map size:"<< m_mapConnection.size();
    emit clientConnected(handle, clientConnection->peerAddress().toString(), clientConnection->peerPort(), m_mapConnection.size());

}

void LTcpServer::slot_clientDisconnect()
{
    LTcpConnection* pLTcpConnection = qobject_cast<LTcpConnection *>(sender());
    qintptr handle = pLTcpConnection->handle();
    QMap<qintptr, LTcpConnection*>::iterator it = m_mapConnection.find(handle);
    if (it != m_mapConnection.end())
    {
        m_mapConnection.remove(handle);
    }
    else
    {
        qDebug()<<"m_mapConnection not find handle:" <<handle << "  map size:"<< m_mapConnection.size();
    }

    qDebug()<<"disconnected:" <<handle << "  map size:"<< m_mapConnection.size();
    //发出信号
    pLTcpConnection->deleteLater();
    emit clientDisconnected(handle);
}
