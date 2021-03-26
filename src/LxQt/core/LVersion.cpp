#include "LVersion.h"
#include <QStringList>
#include <QtDebug>

CLVersion::CLVersion(QString strVersion, QObject *parent)
    : QObject(parent)
    , m_strVersion(strVersion)
    , m_nMajor(0)
    , m_nMinor(0)
    , m_nRevision(0)
{
    QStringList strlstVersion = m_strVersion.split('.');
    if (strlstVersion.size() > 4)
    {
        qDebug() << "版本号格式错误";
        return;
    }
    if (strlstVersion.size() < 2)
    {
        qDebug() << "主版本和子版本号不能省略";
        return;
    }
    bool bMajor = false;
    bool bMinor = false;
    bool bRevision = false;

    m_nMajor = strlstVersion.at(0).toInt(&bMajor);
    m_nMinor = strlstVersion.at(1).toInt(&bMinor);
    if (bMajor || bMinor)
    {
        qDebug() << "主版本和子版本号不能省略";
        return;
    }
    if (strlstVersion.size() > 2)
    {
        m_nRevision = strlstVersion.at(2).toInt(&bRevision);
    }

}

CLVersion::~CLVersion()
{

}

bool CLVersion::operator ==(const CLVersion &rhs)
{
    if (m_nMajor == rhs.m_nMajor && m_nMinor == rhs.m_nMinor && m_nRevision == rhs.m_nRevision)
    {
        return true;
    }
    return false;
}

bool CLVersion::operator >(const CLVersion &rhs)
{
    // 比较主版本号
    if (m_nMajor > rhs.m_nMajor)
    {
        return true;
    }
    if (m_nMajor < rhs.m_nMajor)
    {
        return false;
    }
    // 比较子版本号
    if (m_nMinor > rhs.m_nMinor)
    {
        return true;
    }
    if (m_nMinor < rhs.m_nMinor)
    {
        return false;
    }
    //
    if (m_nRevision > rhs.m_nRevision)
    {
        return true;
    }
    if (m_nRevision < rhs.m_nRevision)
    {
        return false;
    }
    return false;

}

bool CLVersion::operator < (const CLVersion &rhs)
{
    if (*this == rhs)
    {
        return false;
    }
    else if (*this > rhs)
    {
        return false;
    }

    return true;
}





//// 草泥马这段代码害死个人， 以后不要乱加代码 2个main??? 滴血，害得错在哪儿就不知道
//int main()
//{
//    return 0;
//}
