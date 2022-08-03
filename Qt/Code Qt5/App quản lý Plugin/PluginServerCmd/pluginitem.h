#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QObject>
#include <QPluginLoader>
#include <IPlugin.h>

class PluginItem : public QObject
{
    Q_OBJECT
public:
    explicit PluginItem(QObject *parent = nullptr);
    PluginItem(QPluginLoader* loader,InterfaceForPlugin* interface,QObject* parent = nullptr);

    QString getName();

    QPluginLoader *loader;
    InterfaceForPlugin* interface;
    QString filename;
signals:

};

#endif // PLUGINITEM_H
