#include "LTcpClient.h"
#include <QFile>
#include <QDataStream>

#define PACKET_HEAD_2_BYTE      2   // 包总长度标识2字节
#define PACKET_HEAD_BYTE        4   // 包总长度标识所占字节
#define PACKET_CMD_BYTE         4   // 包命令标识所占字节
#define PACKET_SEND_MAX_BYTE    1024
#define FILENAME_MAX_BYTE       4

LTcpClient::LTcpClient(QObject *parent)
    : QTcpSocket(parent)
{

    m_pFileLocal = new QFile();
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(deleteLater()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    //connect(this, SIGNAL(readyRead()), this, SLOT(readData()));

    // 加入socket写入信号, 再在槽函数write文件
    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(writeProgress(qint64)));

}

LTcpClient::~LTcpClient()
{
    m_pFileLocal->deleteLater();
}

void LTcpClient::setIP(const QString &strIp)
{
    m_strIp = strIp;
}

QString LTcpClient::getIP() const
{
    return m_strIp;
}

void LTcpClient::setPort(int nPort)
{
    m_nPort = nPort;
}

int LTcpClient::getPort() const
{
    return m_nPort;
}

bool LTcpClient::connectHost(const QString &strIp, int nPort)
{
    m_strIp = strIp;
    m_nPort = nPort;
    abort();
    connectToHost(m_strIp, m_nPort);
    return true;
}

void LTcpClient::sendFile(unsigned int unCmd, const QString &strFilePath)
{
    m_byteBlock.clear();
    //m_byteBlock.resize(0);

    m_pFileLocal->setFileName(strFilePath);
    if(!m_pFileLocal->open(QFile::ReadOnly))
    {
        qDebug() << "open file error! " + strFilePath;
        return;
    }
    quint64 llFileSize = m_pFileLocal->size();  //文件总大小
    QDataStream out(&m_byteBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    QString strFileName = strFilePath.right(strFilePath.size() - strFilePath.lastIndexOf('/') - 1);

    //m_llBytesTotal = PACKET_HEAD_BYTE + PACKET_CMD_BYTE + FILENAME_MAX_BYTE + llFileSize;

    qDebug()<<"totalByte=" << m_llBytesTotal;

    out << (quint32)0;
    out << (quint32)unCmd;
    out << strFileName.length();
    out << strFileName.toLatin1(); // 此处需要把本地字符集转换成acill
    m_llBytesWritten = 0;
    m_llBytesTotal = m_byteBlock.size() + llFileSize;
    out.device()->seek(0);
    out << m_llBytesTotal;

    //-->暂时先不write File, 为了响应进度函数，在进度条函数里write文件

    m_llBytesToWrite = m_llBytesTotal - write(m_byteBlock);

}

// 前四个字节总长度+4字节命令号+内容
void LTcpClient::sendData(unsigned int unCmd, char *data, unsigned int unSize)
{
    m_byteBlock.clear();
    QDataStream out(&m_byteBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);
    //    out << (quint16)0;
    //    out << (quint16)0;
    out << (quint32)0;
    out << unCmd;
    m_byteBlock.append(data, unSize);
    m_llBytesWritten = 0;
    m_llBytesTotal = m_byteBlock.size();
    // 如果发2字节总长度out.device()->seek(2); out << (quint16)(byteBlock.size()-sizeof(quint16)*2);
    out.device()->seek(0);
    out << m_llBytesTotal; // 包含本身所占的4字节
    m_llBytesToWrite = m_llBytesTotal - write(m_byteBlock);
}


void LTcpClient::writeProgress(qint64 bytes)
{
    m_llBytesWritten += bytes;
    qDebug() << "send:" << m_llBytesWritten;
    emit refProgressBar(m_llBytesWritten, m_llBytesTotal);
    /* 全部发送完 */
    if(m_llBytesWritten == m_llBytesTotal)
    {
        qDebug() << "send finsh:";
        return;
    }
    // 还有文件数据要发
    if(m_llBytesToWrite > 0)
    {
        m_byteBlock = m_pFileLocal->read(qMin(m_llBytesToWrite, (qint64)PACKET_SEND_MAX_BYTE));
        m_llBytesToWrite -= write(m_byteBlock);
        qDebug() << tr("bytesToWrite=%1").arg(m_llBytesToWrite);
    }
    else
    {
        m_pFileLocal->close();
    }

}

