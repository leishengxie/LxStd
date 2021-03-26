#include "LVersionXmlTool.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include "LVersion.h"

CLVersionXmlTool::CLVersionXmlTool(QObject* parent) : QObject(parent)
{

}

void CLVersionXmlTool::createVersionXmlFile(const QString & strXmlFileName, const QList<T_BinFileNodeMsg> & lstBinFileNodeMsg)
{
    QFile file(strXmlFileName);
    if(!file.open(QFile::WriteOnly | QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
    {
        return;
    }
    QDomDocument doc;

    //写入xml头部
    QDomProcessingInstruction instruction; //添加处理命令
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    //添加根节点
    QDomElement root = doc.createElement("filelist");
    doc.appendChild(root);

    //添加子节点
    foreach (T_BinFileNodeMsg tBinFileNodeMsg, lstBinFileNodeMsg)
    {
        QDomElement elementFile = doc.createElement("file");
        elementFile.setAttribute("name", tBinFileNodeMsg.name);
        elementFile.setAttribute("dir", tBinFileNodeMsg.dir);
        elementFile.setAttribute("version", tBinFileNodeMsg.version);
        root.appendChild(elementFile);
    }

    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream, 4); //缩进4格
    file.close();
}

QList<T_BinFileNodeMsg> CLVersionXmlTool::getListVersion(const QString & strFileName)
{
    QList<T_BinFileNodeMsg> lstBinFileNodeMsg;
    if(strFileName.isEmpty())
    {
        return lstBinFileNodeMsg;
    }
    if(!QFile::exists(strFileName))
    {
        //m_strTip="本地的更新文件不存在！";
        return lstBinFileNodeMsg;
    }

    QFile file(strFileName);
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        //m_strTip="不能打开更新文件！";
        return lstBinFileNodeMsg;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    if(!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
        qDebug() << "set content error...";
        return lstBinFileNodeMsg;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if(root.tagName() != "filelist")
    {
        //m_strTip="XML内容错误！";
        return lstBinFileNodeMsg;
    }
    QDomNodeList nodeList = root.elementsByTagName("file");
    for(int i = 0; i < nodeList.size(); i++)
    {
        T_BinFileNodeMsg tBinFileNodeMsg;
        tBinFileNodeMsg.name = nodeList.at(i).toElement().attribute("name");
        tBinFileNodeMsg.dir = nodeList.at(i).toElement().attribute("dir");
        tBinFileNodeMsg.version = nodeList.at(i).toElement().attribute("version");
        lstBinFileNodeMsg.append(tBinFileNodeMsg);
    }
    return lstBinFileNodeMsg;
}

QList<T_BinFileNodeMsg> CLVersionXmlTool::getListVersionDownload(const QList<T_BinFileNodeMsg> & lstBinFileNodeOld
                                                                 , const QList<T_BinFileNodeMsg> & lstBinFileNodeNew
                                                                 , bool bNeedDlelteOldFile)
{
    QList<T_BinFileNodeMsg> lstBinFileNodeMsg;

    // 以新更新文件为基准进行校验
    foreach (T_BinFileNodeMsg tBinFileNodeNew, lstBinFileNodeNew)
    {
        // contains底层实现是std::find
        // 本地XML没有此文件,加入下载列表
        if (!lstBinFileNodeOld.contains(tBinFileNodeNew))
        {
            lstBinFileNodeMsg.append(tBinFileNodeNew);
            continue;
        }

        // 检查版本，如果本地版本低于下载的版本，则加入下载列表
        int nPos = lstBinFileNodeOld.indexOf(tBinFileNodeNew);
        if (-1 == nPos)
        {
            qDebug() << "error, not find";
        }
        T_BinFileNodeMsg tBinFileNodeOld = lstBinFileNodeOld[nPos];
        if ( CLVersion(tBinFileNodeNew.version) > CLVersion(tBinFileNodeOld.version) )
        {
            lstBinFileNodeMsg.append(tBinFileNodeNew);
        }
        else
        {
            qDebug()<< tBinFileNodeNew.name <<"文件是最新版本，不需要更新";
        }
    }
    return lstBinFileNodeMsg;
}

QList<T_BinFileNodeMsg> CLVersionXmlTool::getListVersionDownload(const QString &strFileNameOld
                                                                 , const QString &strFileNameNew
                                                                 , bool bNeedDlelteOldFile)
{
    return getListVersionDownload(getListVersion(strFileNameOld), getListVersion(strFileNameNew), bNeedDlelteOldFile);
}

