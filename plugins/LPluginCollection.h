#ifndef CLPLUGINCOLLECTION_H
#define CLPLUGINCOLLECTION_H

#include <QDesignerCustomWidgetCollectionInterface>

class CLPluginCollection : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    CLPluginCollection(QObject *parent = 0);

    // 注意const不能少了，不然编译器一直说没有实现纯虚函数，害死个人，还是按f1官方例子找到的
    QList<QDesignerCustomWidgetInterface*> customWidgets() const Q_DECL_OVERRIDE;

private:
     QList<QDesignerCustomWidgetInterface*> widgets;

};

#endif // CLPLUGINCOLLECTION_H
