#include "LHttpClient.h"
#include <QtDebug>

#include <QNetworkReply>


/*******google文件包含顺序****/
//xxx.h 假设本文件为xxx.cpp
//C 系统文件
//C++ 系统文件
//其他库的 .h 文件
//本项目内 .h 文件

QVariant LHttpClient::s_varCookies;

LHttpClient::LHttpClient(QObject* parent)
    : QObject(parent)
{
    init();
}


LHttpClient::~LHttpClient()
{
    //m_netAccessManager->deleteLater();

}

void LHttpClient::init()
{

    m_netAccessManager = new QNetworkAccessManager(this);
    //connect(m_netAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
}


void LHttpClient::get(const QUrl & urlRequest, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    m_request.setUrl(urlRequest);
//     m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-protobuf");
//    m_request.setRawHeader("Connection", "keep-alive");
    m_netReply = m_netAccessManager->get(m_request);
    connect(m_netReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_netReply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(m_netReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(m_netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
}

void LHttpClient::post(const QUrl & urlRequest, const void* pData, int nDataLen, int nTimeout)
{
    post(urlRequest, QByteArray((const char*)pData, nDataLen), nTimeout);
}

void LHttpClient::post(const QUrl &urlRequest, const QByteArray &data, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    m_request.setUrl(urlRequest);
    m_netReply = m_netAccessManager->post(m_request, data);
    connect(m_netReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_netReply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(m_netReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(m_netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
}

LHttpClient::setCookies(const QVariant &varCookies)
{
    s_varCookies = varCookies;
}


void LHttpClient::onReadyRead()
{
    m_httpDataBuffer.push_back(m_netReply->readAll());
}

void LHttpClient::onError(QNetworkReply::NetworkError errorCode)
{
    qDebug() << "NetworkError:"  << errorCode;
}

void LHttpClient::onFinished()
{
    qDebug() << "parent LHttpDownload";
    QVariant status_code = m_netReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QNetworkReply::NetworkError eNetworkError = m_netReply->error();
    m_netReply->deleteLater();
    m_netReply = NULL;

    if(eNetworkError == QNetworkReply::NoError)
    {
        emit finished(m_httpDataBuffer.readAll());
        m_httpDataBuffer.clear();
        qDebug() << "success"  << status_code; //200
    }
    else
    {
        qDebug() << "failed" << status_code;
    }

}




void LHttpClient::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    emit uploadProgress(bytesSent, bytesTotal);
}

void LHttpClient::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    emit downloadProgress(bytesReceived, bytesTotal);
}



