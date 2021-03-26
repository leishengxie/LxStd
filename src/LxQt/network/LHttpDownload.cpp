#include "LHttpDownload.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QEventLoop>
#include <QDir>



LHttpDownload::LHttpDownload(QObject* parent)
    : LHttpClient(parent)
    , m_nCurTaskId(-1)
    , m_nIdAutoIncrementIndex(-1)
{

}

LHttpDownload::~LHttpDownload()
{

}


///
/// \brief LHttpDownload::download  下载单个文件
/// \param urlRequest   url
/// \param strFileName  保存的文件名
/// \param strDir   保存的目录路径
/// \param nTimeout
///
void LHttpDownload::download(const QUrl & urlRequest, const QString & strFileName, const QString & strPath, int nTimeout)
{
    addTask(urlRequest, strFileName, strPath);
    start();
}

///
/// \brief LHttpDownload::downloadList  下载多个文件
/// \param strlstUrls
/// \param strPath
///
void LHttpDownload::downloadList(const QStringList & strlstUrls, const QString & strPath)
{
    foreach(QString url, strlstUrls)
    {
        addTask(url, "", strPath);
    }
    start();
}

// 获取要下载文件的大小
qint64 LHttpDownload::getFileTotalSize(QString url, int tryTimes)
{
    qint64 size = -1;

    if (tryTimes <= 0)
    {
        tryTimes = 1;
    }

    do
    {
        QEventLoop loop;
        QTimer timer;
        m_netReply = m_netAccessManager->head(QNetworkRequest(url)); //发出请求，获取文件地址的头部信息;
        if (!m_netReply)
        {
            continue;
        }
        connect(m_netReply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

        // 阻塞2000ms等待获取文件大小信息
        timer.start(2000);
        loop.exec();

        if (m_netReply->error() != QNetworkReply::NoError)
        {
            qDebug() << m_netReply->errorString();
            continue;
        }
        else if (!timer.isActive())
        {
            // 请求超时超时,未获取到文件信息;
            qDebug() << "Request Timeout";
            continue;
        }
        timer.stop();

        QVariant varSize = m_netReply->header(QNetworkRequest::ContentLengthHeader);
        size = varSize.toLongLong();
        m_netReply->deleteLater();
        break;
    }
    while (tryTimes--);

    return size;
}

T_TaskDownloadInfo LHttpDownload::getTaskInfoById(int nTaskId)
{
    foreach (T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        if (tTaskDownloadInfo.taskInfoListId == nTaskId)
        {
            return tTaskDownloadInfo;
        }
    }
}

///
/// \brief LHttpDownload::start 开始下载
///
void LHttpDownload::start()
{
    if (m_listTaskDownloadInfo.isEmpty())
    {
        return;
    }

    // 正在下载
    if (m_nCurTaskId != -1)
    {
        return;
    }

    // 指向下个任务
    foreach (T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        if(tTaskDownloadInfo.eDowlLoadState == ED_Ready)
        {
            m_tTaskCur = tTaskDownloadInfo;
            m_nCurTaskId = tTaskDownloadInfo.taskInfoListId;
            get(tTaskDownloadInfo.url);
            break;
        }
    }
}

void LHttpDownload::pause()
{

}

void LHttpDownload::stop()
{
//    disconnect(m_netReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
//    disconnect(m_netReply, SIGNAL(finished()), this, SLOT(onFinished()));
//    disconnect(m_netReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
//    disconnect(m_netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));

}

void LHttpDownload::addTask(const QUrl & urlRequest, const QString & strFileName, const QString & strPath)
{
    // 添加新文件任务到任务列表
    T_TaskDownloadInfo tTaskDownloadInfo;
    // 文件名
    if(strFileName.isEmpty())
    {
        QFileInfo fileInfo(urlRequest.path());
        tTaskDownloadInfo.rename = fileInfo.fileName();
    }
    else
    {
        tTaskDownloadInfo.rename = strFileName;
    }

    //文件夹为空则默认当前程序运行路径
    if(strPath.isEmpty())
    {
        tTaskDownloadInfo.dirSaveTo = QDir::currentPath();
    }
    else
    {
        QDir dir(strPath);
        //没有此文件夹，则创建
        if( !dir.exists() )
        {
            dir.mkpath(strPath);
        }
        tTaskDownloadInfo.dirSaveTo = strPath;
    }
    tTaskDownloadInfo.taskInfoListId = ++m_nIdAutoIncrementIndex;
    tTaskDownloadInfo.url = urlRequest;
    tTaskDownloadInfo.size = getFileTotalSize(tTaskDownloadInfo.url.url());
    m_listTaskDownloadInfo.append(tTaskDownloadInfo);
}

void LHttpDownload::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // 更新单个任务进度
    for (QList<T_TaskDownloadInfo>::iterator iter = m_listTaskDownloadInfo.begin() ; iter != m_listTaskDownloadInfo.end() ; ++iter)
    {
        if((*iter).taskInfoListId == m_nCurTaskId)
        {
            (*iter).completed = bytesReceived;
            break;
        }
    }
    emit downloadProgress(bytesReceived, bytesTotal);

    // 更新总进度
    quint64 llSizeTotal = 0;
    quint64 llSizeAlready = 0;
    foreach(T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        llSizeAlready += tTaskDownloadInfo.completed;
        llSizeTotal += tTaskDownloadInfo.size;
    }
    emit downloadProgressAll(llSizeAlready, llSizeTotal);
}

void LHttpDownload::onFinished()
{
    //如果文件已经存在，那么删除
    qDebug() << "child LHttpDownload";
    if(QFile::exists(m_tTaskCur.filePath()))
    {
        QFile::remove(m_tTaskCur.filePath());
    }

    // 单个任务下载完成
    QFile file(m_tTaskCur.filePath());
    // 20200101 这里QIODevice::WriteOnly修改为QIODevice::Truncate | QIODevice::WriteOnly 不然有麻烦
    if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        qDebug() << "不能存储文件：" << m_tTaskCur.filePath();
        return;
    }
    file.write(m_httpDataBuffer.readAll());
    file.flush();//注意需要刷新
    file.close();
    m_httpDataBuffer.clear();   // 注意清除
    m_netReply->deleteLater();
    m_netReply = NULL;
    for (QList<T_TaskDownloadInfo>::iterator iter = m_listTaskDownloadInfo.begin() ; iter != m_listTaskDownloadInfo.end() ; ++iter)
    {
        if((*iter).taskInfoListId == m_nCurTaskId)
        {
            (*iter).eDowlLoadState = ED_Completed;
            break;
        }
    }
    emit downloadCompleted(m_tTaskCur);

    // 任务列表状态更新
    bool bCompletedAll = true;
    foreach(T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        if (tTaskDownloadInfo.eDowlLoadState != ED_Completed)
        {
            bCompletedAll = false;
            break;
        }
    }
    if (bCompletedAll)
    {
        emit finishedAllTask();
        return;
    }

    // 开始下个任务
    m_nCurTaskId = -1;
    start();

    //        // 写文件-形式为追加
    //        QFile file(m_strBaseName + ".jpg");
    //        if (file.open(QIODevice::Append))
    //        {
    //            //if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    //                file.write(m_pReply->readAll());
    //            file.close();
    //        }
    //            QString strFileName = m_strBaseName + ".png";
    //               QImageWriter imageWriter;
    //               imageWriter.setFormat("png");
    //               imageWriter.setFileName(strFileName);
    //               if( imageWriter.canWrite() )
    //               {
    //                  imageWriter.write( QImage(m_strBaseName + ".jpg", "jpg") );
    //               }

}





