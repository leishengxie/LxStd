/***************************************************************************
 * lx
 * qt http 客户端简单封装
 * ************************************************************************/
// qt4x分别使用QFtp和QHttp，5以后统一用QNetworkAccessManager 提供了HTTP、HTTPS、FTP等高级API
// QNetworkRequest 专门用于请求的，
// QNetworkReply 接收请求的响应
//客户端发送一个HTTP请求到服务器的请求消息包括以下格式：请求行（request line）、请求头部（header）、空行和请求数据四个部分组成，
//下图给出了请求报文的一般格式。请求行组成：请求方法+空格+url+空格+协议版本+回车符+换行符。详情见HTTP 消息结构

// 看别人代码出现以下问题
// 写这么多try catch干嘛？Qt又不会抛异常
// QNetworkAccessManager本来就是多线程的，所以不需要再搞个线程了。而且你如果真在次线程中，也是不能弹QMessageBox的！
#ifndef L_HTTP_CLIENT
#define L_HTTP_CLIENT

#include <QObject>
#include <QUrl>

#include <QNetworkRequest>
#include <QNetworkReply>

class QNetworkAccessManager;
//class QNetworkReply;

/***************处理来自http readyRead的数据********************/
class LHttpDataBuffer : public QList<QByteArray>
{
public:

    void append(const QByteArray& data)
    {
        QList<QByteArray>::append(data);
    }

    int byteLength() const
    {
        int nByteLength = 0;
        QList<QByteArray>::const_iterator itor = begin();
        for ( ; end() != itor; ++itor)
        {
            nByteLength += (*itor).size();
        }
        return nByteLength;
    }

    int read(void* pBuffer, int nBufLen)
    {
        int nRead = 0;
        while (nRead < nBufLen && !empty())
        {
            QByteArray& data = *begin();
            const int nDataLen = data.size();
            const int nCopyLen = std::min(nDataLen, nBufLen - nRead);
            memcpy(((char*)pBuffer) + nRead, data.data(), nCopyLen);
            if (nCopyLen == nDataLen)
            {
                pop_front();
            }
            else
            {
                data.remove(0, nCopyLen);
            }
            nRead += nCopyLen;
        }
        return nRead;
    }

    QByteArray readAll()
    {
        QByteArray data;
        data.reserve(byteLength());
        QList<QByteArray>::iterator itor = begin();
        for ( ; end() != itor; ++itor)
        {
            data.append(*itor);
        }
        return data;
    }
};


class LHttpClient : public QObject
{
       Q_OBJECT
public:
    explicit LHttpClient(QObject *parent = 0);
    virtual ~LHttpClient();

    // http协议的get相当于下载
    void get(const QUrl& urlRequest, int nTimeout = 6000);

    // http协议的post相当于上传
    void post(const QUrl& urlRequest, const void* pData, int nDataLen, int nTimeout = 6000);
    void post(const QUrl& urlRequest, const QByteArray& data, int nTimeout = 6000);

    static setCookies(const QVariant & varCookies);

signals:
    void finished(const QByteArray& data);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);       // 上传
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal); // 下载

protected slots:
    //响应m_netReply有新的数据到达
   void onReadyRead();
   void onError(QNetworkReply::NetworkError errorCode);
   void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
   virtual void onDownloadProgress(qint64 bytesReceived,qint64 bytesTotal);
   virtual void onFinished();


private:
   void init();


protected:
   QNetworkAccessManager *m_netAccessManager;   // 接入管理
   QNetworkReply *m_netReply;                   // Reply回复, 专门接收请求的响应
   QNetworkRequest m_request;                   // 专门用于请求的

   LHttpDataBuffer m_httpDataBuffer;            // 接收数据

private:
   // 每个LHttpClient 共用的数据，即登录后每次http请求都是一样的cookies
   static QVariant s_varCookies;

};

#endif // L_HTTP_CLIENT
