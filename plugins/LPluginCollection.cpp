#include "LPluginCollection.h"
#include "LProgressIndicatorPlugin.h"
#include "LSwitchButtonPlugin.h"

CLPluginCollection::CLPluginCollection(QObject *parent)
: QObject(parent)
{
    widgets.append(new CLProgressIndicatorPlugin(this));
    widgets.append(new CLSwitchButtonPlugin(this));
}

QList<QDesignerCustomWidgetInterface *> CLPluginCollection::customWidgets() const
{
    return widgets;
}


//#if QT_VERSION < 0x050000
//Q_EXPORT_PLUGIN2(CLPluginCollection, CLPluginCollection)
//#endif // QT_VERSION < 0x050000
