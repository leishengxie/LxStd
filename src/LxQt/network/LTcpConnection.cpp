#include "LTcpConnection.h"
//#include "crypto/LEncrypt.h"
#include <QDataStream>
#include <QtDebug>
#include <QThread>

int Lkey[] = { 2, 1, 3, 4, 5 };

LTcpConnection::LTcpConnection(qintptr handle, QObject *parent)
    : QTcpSocket(parent)
    , m_Handle(handle)
    , m_unBlockSize(0)
    , m_nCmd(-1)
{
    setSocketDescriptor(m_Handle); //区分其它连接
    //当disconnected()时当前socket的socketDescriptor()都会变成-1
    //断开连接消息
//    connect(this, &LTcpConnection::disconnected, [&](){
//        deleteLater();
//        emit this->disconnected(socketDescriptor());
//        qDebug() << ".......1 disconnected";
//    });
    //connect(this, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readData()));

}


//主动断开连接槽
void LTcpConnection::doDisconnectSocket(qintptr handle)
{
    if (handle == m_Handle)
    {
        disconnectFromHost();
        //waitForDisconnected();
    }
}

/*
 * class A
{
public:
    void fun ( void )
    {
        static int a = 1;
        a++;
        cout << a << endl;
    }
};
int main()
{
    A *p = new A;

    p->fun(); //2
    p->fun(); //3
    delete p;
    p = NULL;
    p = new A;

    p->fun(); //############4 怎么改才能让他打印2

    return 0;
}
*/

void LTcpConnection::readData()
{
    qDebug() << QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId());
    //QTcpSocket *socket=qobject_cast<QTcpSocket*>(sender());
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_4);
    //static quint32 unBlockSize = 0; //bug, delete 类实例但unBlockSize是全局的，新实例中的unBlockSiz还是上一次unBlockSize的值，所以本处
                                    //需要修改
    //static int nCmd = -1;
    //如果是新消息
    if (0 == m_unBlockSize)
    {
        if (bytesAvailable() < 8)
        {
            qDebug() << "data head must 8 byte or more";
            disconnectFromHost();
            return ;
        }
        in >> m_unBlockSize;
        in >> m_nCmd;
        qDebug() << QString("new msg m_unBlockSize=%1, m_nCmd=%2").arg(m_unBlockSize).arg(m_nCmd);
    }

    if (bytesAvailable() < m_unBlockSize - sizeof(int) - sizeof(quint16) * 2)
    {
        //继续接收
        qDebug() << "m_unBlockSize=" << m_unBlockSize << "  bytesAvailable="+ QString::number(bytesAvailable());
        return ;
    }

    qDebug() << "recv content length:" << bytesAvailable();
    // 先不用主命令号 解析文件
    if (m_nCmd == 255)
    {
        quint32 unFileNameLength;
        in >> unFileNameLength;
        QString strFileName = read(unFileNameLength);
        qDebug() << "file name length:" << unFileNameLength << "file name:" << strFileName;
        QByteArray byteArray = read(m_unBlockSize - sizeof(int) - sizeof(quint16) * 2 - sizeof(int) - unFileNameLength);
        emit recvFile(m_Handle, m_nCmd, strFileName, byteArray);
    }
    else
    {
        QByteArray byteArray = read(m_unBlockSize - sizeof(int) - sizeof(quint16) * 2); //这里吧readAll改为实际应当读取的长度
        char *data = byteArray.data();

        // 解密处理
        //Cutecode(data, Lkey);

        emit recv(m_Handle, m_nCmd, data);
    }

    m_unBlockSize = 0;
    m_nCmd = -1;

}




