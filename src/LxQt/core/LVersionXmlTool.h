#ifndef CLVERSIONXMLTOOL_H
#define CLVERSIONXMLTOOL_H

#include <QObject>

///
/// \brief The T_BinFileNodeMsg struct 序列化的xml节点为版本信息文件
/// eg: xml文件路径为d://aa/version.xml
///     当前文件路径为d://aa/dd/ee/abc.dll
///
struct T_BinFileNodeMsg
{
    QString name;       // 版本文件名 abc.dll
    QString dir;        // 版本文件所在的目录, 注意是指相对于xml文件之后所在的目录，本例为dd/ee
    QString version;    // 版本号
    T_BinFileNodeMsg()
    {
        init();
    }

    void init()
    {
        name = "";
        dir = "";
        version = "";
    }

    // 定义仿函数实现查找
    bool operator()(const T_BinFileNodeMsg & rhs)
    {
        return name == rhs.name;
    }

    // indexOf
    bool operator == (const T_BinFileNodeMsg & rhs)
    {
        return name == rhs.name;
    }
};


///
/// \brief The CLVersionXmlTool class 基于xml文件的处理工具类
///
class CLVersionXmlTool : public QObject
{
    Q_OBJECT
public:
    explicit CLVersionXmlTool(QObject *parent = 0);

    static void createVersionXmlFile(const QString & strXmlFileName, const QList<T_BinFileNodeMsg> & lstBinFileNodeMsg);
    static QList<T_BinFileNodeMsg> getListVersion(const QString & strFileName);
    static QList<T_BinFileNodeMsg> getListVersionDownload(const QList<T_BinFileNodeMsg> & lstBinFileNodeOld
                                                   , const QList<T_BinFileNodeMsg> & lstBinFileNodeNew
                                                   , bool bNeedDlelteOldFile = false);
    static QList<T_BinFileNodeMsg> getListVersionDownload(const QString & strFileNameOld
                                                   , const QString & strFileNameNew
                                                   , bool bNeedDlelteOldFile = false);


signals:

public slots:
};

#endif // CLVERSIONXMLTOOL_H
