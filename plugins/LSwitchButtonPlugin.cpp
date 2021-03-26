#include "buttons/LSwitchButton.h"
#include "LSwitchButtonPlugin.h"

#include <QtPlugin>

CLSwitchButtonPlugin::CLSwitchButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CLSwitchButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CLSwitchButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CLSwitchButtonPlugin::createWidget(QWidget *parent)
{
    return new CLSwitchButton(parent);
}

///
/// \brief CLSwitchButtonPlugin::name 返回的字符串表示该自定义插件名称
/// \return
///
QString CLSwitchButtonPlugin::name() const
{
    return QLatin1String("CLSwitchButton");
}

///
/// \brief CLSwitchButtonPlugin::group 在group()函数中返回的字符创表示自定义插件在设计器中属于哪个分组，
/// 如Qt Creator中有Buttons，DisplayWidgets等分组，这里设为LxWidgets；
/// \return
///
QString CLSwitchButtonPlugin::group() const
{
    return QLatin1String("LxWidgets");
}

QIcon CLSwitchButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/img/CLSwitchButton.png"));
}

QString CLSwitchButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CLSwitchButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CLSwitchButtonPlugin::isContainer() const
{
    return false;
}

///
/// \brief CLSwitchButtonPlugin::domXml 返回的字符串是使用该插件时设计器自动生成的UI文件代码段，保持默认
/// \return
///
QString CLSwitchButtonPlugin::domXml() const
{
    //类名-对象名
    return QLatin1String("<widget class=\"CLSwitchButton\" name=\"switchButton\">\n</widget>\n");
}

///
/// \brief CLSwitchButtonPlugin::includeFile 回的字符串表示使用该插件时自动添加的包含文件，这里改为
/// \return
///
QString CLSwitchButtonPlugin::includeFile() const
{
    return QLatin1String("LxWidgets/LSwitchButton.h");
}
//#if QT_VERSION < 0x050000
//Q_EXPORT_PLUGIN2(CLSwitchButtonPlugin, CLSwitchButtonPlugin)
//#endif // QT_VERSION < 0x050000


