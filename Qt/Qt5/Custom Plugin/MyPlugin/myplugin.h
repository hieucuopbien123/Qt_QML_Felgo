#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QObject>
#include "IPlugin.h"
#include <QtPlugin>
#include <QMessageBox>

class MyPlugin : public QObject,InterfaceForPlugin
{
    Q_OBJECT
    Q_INTERFACES(InterfaceForPlugin)
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    Q_PLUGIN_METADATA(IID "test interface")
#endif
public:
    MyPlugin(QObject *parent = nullptr);
    void functOfPlugin(const QString& mess) const;
};

#endif // MYPLUGIN_H
