#ifndef LTCPCLIENT_H
#define LTCPCLIENT_H

#include <QTcpSocket>

class QFile;

class LTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit LTcpClient(QObject *parent = 0);
    ~LTcpClient();

signals:
    void refProgressBar(qint64 llBytesWritten, qint64 llBytesTotal);

public:
    void setIP(const QString &strIp);
    QString getIP()const;

    void setPort(int nPort);
    int getPort()const;

    bool connectHost(const QString &strIp, int nPort);
    void sendFile(unsigned int unCmd, const QString &strFilePath);
    void sendData(unsigned int unCmd, char* data, unsigned int unSize);

private slots:
    void writeProgress(qint64 bytes);


private:
    QString m_strIp;
    int m_nPort;
    QByteArray m_byteBlock;

    // 发送文件及显示进度相关
    QFile *m_pFileLocal;                // 要发送的本地文件
    qint64 m_llBytesTotal;              // 要发送的所有内容总长度
    qint64 m_llBytesWritten;            // 已经发送的内容
    qint64 m_llBytesToWrite;            // 剩下的内容字节数

};

#endif // LTCPCLIENT_H
