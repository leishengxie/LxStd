#ifndef LVERSION_H
#define LVERSION_H

#include <QObject>

// 使用qt自带的
//#include <QVersionNumber>

/****************软件版本命名规范 (GNU 风格)******/
//1、初始化项目时，版本号可以为 0.1 或 0.1.0，如果你比较高调的话，可以使用 1.0 或 1.0.0
//2、当项目进行了局部修改或 bug 修复时，主版本号 和 子版本号 不变，修正版本号 加 1
//3、当项目在原有的基础上增加了部分功能时，主版本号 不变，子版本号 加 1，修正版本号复位为 0
//4、当项目进行了重大修改或局部修正累积较多而导致的项目整体发生变化，主版本号 加 1，子版本号 和 修正版本号 复位为 0
//5、编译版本号一般为编译器在编译过程中自动生成，只定义其格式，并不进行人为控制
//主版本号 . 子版本号 [. 修正版本号 [. 编译版本号 ]]
//Major_Version_Number.Minor_Version_Number[.Revision_Number[.Build_Number]]
//示例 : 1.2.1, 2.0, 5.0.0 build-13124
// 主版本号 . 子版本号为必选

/**************************** X.Y.Z.build windows软件版本 --与上面一样 ****************************/
/**************************** X.Y.Z.build windows产品版本 ****************************/

///
/// \brief The CLVersion class 规则都是由人定的，自定义的版本号比较规则， 与Windows，gun风格相同
/// x.y.z.build
///
class CLVersion : public QObject
{
    Q_OBJECT

public:
    explicit CLVersion(QString strVersion, QObject *parent = 0);
    ~CLVersion();

    bool operator == (const CLVersion & rhs);
    bool operator > (const CLVersion & rhs);
    bool operator < (const CLVersion & rhs);


public:
    int m_nMajor;           // 主版本号
    int m_nMinor;           // 子版本号
    int m_nRevision;        // 修正版本号
                            // 编译版本号可以不用管

    QString m_strVersion;

    // 使用qt自带的
    //QVersionNumber m_versionNumber;
};


#endif //LVERSION_H
