#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QObject>
#include <QString>

class InterfaceForPlugin
{
public:
    virtual void functOfPlugin(const QString& mess);
};

Q_DECLARE_INTERFACE(InterfaceForPlugin,"test interfacfe")

#endif // IPLUGIN_H
