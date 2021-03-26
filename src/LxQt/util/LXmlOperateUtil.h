
/*********************************************************************************
 * 一些常用的xml操作
 *
 * *******************************************************************************/

// 通过QXmlStreamReader解析mxl
// 通过DOM方式 -- 本类使用此方法
// 通过QXmlSimpleReader

#ifndef L_XML_OPERATE_UTIL_H
#define L_XML_OPERATE_UTIL_H


#include <QObject>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

class CLXmlOperateUtil : public QObject
{
    Q_OBJECT

public:
    CLXmlOperateUtil(QObject *parent = 0);
    CLXmlOperateUtil(const QString strXmlFile, QObject *parent = 0);
    ~CLXmlOperateUtil();

    // 静态方法


public:
    // 公共成员方法
    bool loadXmlFile(const QString strXmlFile);
    bool saveXmlFile(const QString strXmlFile);
    QString getFirstElementTextByTagName(const QString &tagName);
    void setFirstElementTextByTagName(const QString &tagName, const QString &text);
    void clearAllChildNodes();

private:
    QDomDocument m_doc;         //xml doc
    QDomNode m_nodeRoot;
    QDomElement m_elementRoot;  //根节点
};

#endif //L_XML_OPERATE_UTIL_H

