#ifndef LREDLABELPLUGIN_H
#define LREDLABELPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class CLProgressIndicatorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT

    // 告诉moc第二个基类为一个插件接口类
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    CLProgressIndicatorPlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool m_initialized;
};

#endif
