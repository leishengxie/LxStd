#ifndef LQt_FUNC_H
#define LQt_FUNC_H

#include "LStd.h"
#include <QString>

class QWidget;

class CLQt : public CLStd
{

public:


    /// 字符串操作
    static QString strRecombine(const QString &strSrc, const QString &strSplit, int nSplitSize);
    // 字符串格式化
    static QString formatBytes(quint64 qu64Size, quint8 u8ValidDigit = 2);

    // 图片处理
    static void saveImgDataToFile(const QString &fromImgData, const QString &toFilePath, const QString &strFormat);
    static void dataToPic(const QString &fromFilePath, QString toPic, QString myformat);

    // 睡眠，延迟
    static void sleep(int ms);
    static void delayTime(int s);

    //窗体相对桌面居中显示
    static void moveToDeskCenter(QWidget *widget);
    static void moveToCenter(QWidget *widgetChild, QWidget *widgetParent);

    //判断是否是IP地址
    static bool isIP(QString strIP);

    //设置为开机启动
    static void autoRunWithSystem(bool bAutoRun, const QString & strAppName, const QString & strAppPath);


}; // end namespace Lx


#endif // end LQt_FUNC_H
