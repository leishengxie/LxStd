#include "LXmlOperateUtil.h"
#include <QFile>
#include <QtDebug>


CLXmlOperateUtil::CLXmlOperateUtil(QObject *parent)
{

}

CLXmlOperateUtil::CLXmlOperateUtil(const QString strXmlFile, QObject *parent)
{
    loadXmlFile(strXmlFile);
}

CLXmlOperateUtil::~CLXmlOperateUtil()
{

}

// 把xml文件中的内容加载后生成QDomDocument
bool CLXmlOperateUtil::loadXmlFile(const QString strXmlFile)
{
    QFile file(strXmlFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << tr("open file %1 fail.").arg(strXmlFile);
        return false;
    }

    if (!m_doc.setContent(&file))
    {
        qDebug() << "QDomDocument setContent fail.";
        file.close();
        return false;
    }
    file.close();
    return true;
}


// 将QDomDocument中的xml信息保存到文件中
bool CLXmlOperateUtil::saveXmlFile(const QString strXmlFile)
{
    QFile file(strXmlFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << tr("open file %1 fail.").arg(strXmlFile);
        return false;
    }

    QTextStream out(&file);
    m_doc.save(out, 4);

    file.close();
    return true;
}

// 在xml文档根节点寻找指定tagName的一级节点list，找到，则返回该节点list的第一个的内容
QString CLXmlOperateUtil::getFirstElementTextByTagName(const QString &tagName)
{
    QString strContent = "";
    QDomNodeList nodeList = m_doc.documentElement().elementsByTagName(tagName);
    if (0 == nodeList.size())
    {
        qDebug() << tr("not find elements: %1").arg(tagName);
        return strContent;
    }
    return nodeList.at(0).toElement().text();
}

// 在指定的xml节点的子节点cmdElem中寻找指定tagName的第一个节点，找到，则修改该节点的text
void CLXmlOperateUtil::setFirstElementTextByTagName(const QString &tagName, const QString &text)
{
    // 根节点
    m_elementRoot = m_doc.documentElement();
    QDomNodeList nodeList = m_elementRoot.elementsByTagName(tagName);
    if (0 == nodeList.size())
    {
        qDebug() << tr("not find elements: %1").arg(tagName);
        return ;
    }
    nodeList.at(0).firstChild().setNodeValue(text);
}

// 删除所有子节点
void CLXmlOperateUtil::clearAllChildNodes()
{
   // m_nodeRoot.clear();
    while (!(m_nodeRoot.firstChild().isNull()))
    {
        m_nodeRoot.removeChild(m_nodeRoot.firstChild());
    }
}

