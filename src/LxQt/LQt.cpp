#include "LQt.h"

#include <QTime>

#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QBuffer>
#include <QSettings>

// 延迟时间-秒
void CLQt::delayTime(int s)
{
    QTime t = QTime::currentTime().addMSecs(s);
    while(QTime::currentTime() < t)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

///
/// \brief Lx::strRecombine 对传入的字符串进行重排，每超过nSplitSize个字节就插入分割字符串strSplit,多用于文本分行显示
/// \param strSrc
/// \param strSplit
/// \param nSplitSize
/// \return
///
QString CLQt::strRecombine(const QString & strSrc, const QString & strSplit, int nSplitSize)
{
    if (strSrc.size() <= nSplitSize)
    {
        return strSrc;
    }
    QString strTemp = strSrc;
    QString strResult = "";
    while (true)
    {
        QString strSub = strTemp.left(nSplitSize);
        strResult = strResult + strSub + strSplit;
        strTemp = strTemp.right(strTemp.size() - nSplitSize);
        if (strTemp.size() <= nSplitSize)
        {
            strResult = strResult + strTemp;
            break;
        }
    }
    return strResult;
}



QString CLQt::formatBytes(quint64 qu64Size, quint8 u8ValidDigit)
{
    QString strUnit = "B";
    double dNumber = qu64Size;
    double dDivisor = 1024;
    if (dNumber >= dDivisor)
    {
        strUnit = "KB";
        dNumber = dNumber / dDivisor;
    }
    if (dNumber >= dDivisor)
    {
        strUnit = "MB";
        dNumber = dNumber / dDivisor;
    }
    if (dNumber >= dDivisor)
    {
        strUnit = "GB";
        dNumber = dNumber / dDivisor;
    }
    if (dNumber >= dDivisor)
    {
        strUnit = "TB";
        dNumber = dNumber / dDivisor;
    }
    return QString::number(dNumber, 'f', u8ValidDigit) + strUnit;
}

void CLQt::saveImgDataToFile(const QString & fromImgData, const QString & toFilePath, const QString & strFormat)
{
    QImage img(fromImgData);
    QByteArray ba;
    QBuffer buf(&ba);
    img.save(&buf, "JPG"); //按照JPG解码保存数据
    QByteArray cc = qCompress(ba, 1);
    QByteArray hh;
    if (strFormat == "Hex")
    {
        hh = cc.toHex(); //16进制数据
    }
    else
    {
        hh = cc.toBase64(); //base64数据
    }
    QString str(hh);
    QFile file(toFilePath);
    if (file.open(QFile::WriteOnly))
    {
        file.write(str.toLatin1());
        file.close();
    }
}

void CLQt::dataToPic(const QString & fromFilePath, QString toPic, QString myformat)
{
    QFile file(fromFilePath);
    if (file.open(QFile::ReadOnly))
    {
        QByteArray read = file.readAll();
        file.close();
        QString ss = QString::fromLatin1(read.data(), read.size());
        QByteArray rc;
        if (myformat == "Hex")
        {
            rc = QByteArray::fromHex(ss.toLatin1());
        }
        else
        {
            rc = QByteArray::fromBase64(ss.toLatin1());
        }
        QByteArray rdc = qUncompress(rc);

        QImage img;
        img.loadFromData(rdc);
        img.save(toPic);
    }
}

void CLQt::sleep(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while ( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    //#ifdef _WIN32
    //Sleep(sec);
    //#else
    //#include <unistd.h>
    //usleep(sec*1000);
    //#endif

}

void CLQt::moveToDeskCenter(QWidget *widget)
{
    moveToCenter(widget, (QWidget *)QApplication::desktop());
}

void CLQt::moveToCenter(QWidget *widgetChild, QWidget *widgetParent)
{
    widgetChild->move(widgetParent->width() * 0.5 - widgetChild->width() * 0.5
                      , widgetParent->height() * 0.5 -  widgetChild->height() * 0.5);
}



bool CLQt::isIP(QString strIP)
{
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(strIP);
}

//QString strAppPath = QApplication::applicationFilePath();
//QString strAppName = QApplication::applicationName();
void CLQt::autoRunWithSystem(bool bAutoRun, const QString &strAppName, const QString &strAppPath)
{
    // HKEY_LOCAL_MACHINE 需要管理员权限
    //QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
                       , QSettings::NativeFormat);
    //qDebug() << settings.allKeys();

    QString strAppPathValue = strAppPath;
    strAppPathValue = strAppPathValue.replace("/","\\");
    if(bAutoRun)
    {
        settings.setValue(strAppName, strAppPathValue);
    }
    else
    {
        settings.remove(strAppName);
    }
}
