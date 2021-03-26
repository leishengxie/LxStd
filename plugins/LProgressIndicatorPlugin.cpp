#include "LProgressIndicator.h"
#include "LProgressIndicatorPlugin.h"

#include <QtPlugin>

CLProgressIndicatorPlugin::CLProgressIndicatorPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CLProgressIndicatorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CLProgressIndicatorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CLProgressIndicatorPlugin::createWidget(QWidget *parent)
{
    return new CLProgressIndicator(parent);
}

///
/// \brief CLProgressIndicatorPlugin::name 返回的字符串表示该自定义插件名称
/// \return
///
QString CLProgressIndicatorPlugin::name() const
{
    return QLatin1String("CLProgressIndicator");
}

///
/// \brief CLProgressIndicatorPlugin::group 在group()函数中返回的字符创表示自定义插件在设计器中属于哪个分组，
/// 如Qt Creator中有Buttons，DisplayWidgets等分组，这里设为LxWidgets；
/// \return
///
QString CLProgressIndicatorPlugin::group() const
{
    return QLatin1String("LxWidgets");
}

QIcon CLProgressIndicatorPlugin::icon() const
{
    return QIcon(QLatin1String(":/img/CLProgressIndicator.png"));
}

QString CLProgressIndicatorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CLProgressIndicatorPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CLProgressIndicatorPlugin::isContainer() const
{
    return false;
}

///
/// \brief CLProgressIndicatorPlugin::domXml 返回的字符串是使用该插件时设计器自动生成的UI文件代码段，保持默认
/// \return
///
QString CLProgressIndicatorPlugin::domXml() const
{
    //类名-对象名
    return QLatin1String("<widget class=\"CLProgressIndicator\" name=\"progressIndicator\">\n</widget>\n");
}

///
/// \brief CLProgressIndicatorPlugin::includeFile 回的字符串表示使用该插件时自动添加的包含文件，这里改为
/// \return
///
QString CLProgressIndicatorPlugin::includeFile() const
{
    return QLatin1String("LxWidgets/LProgressIndicator.h");
}
//#if QT_VERSION < 0x050000
//Q_EXPORT_PLUGIN2(CLProgressIndicatorPlugin, CLProgressIndicatorPlugin)
//#endif // QT_VERSION < 0x050000

