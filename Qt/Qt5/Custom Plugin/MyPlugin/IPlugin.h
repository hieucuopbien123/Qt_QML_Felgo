#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QObject>
#include <QString>
#include <QMessageBox>

class InterfaceForPlugin
{
public:
    virtual void functOfPlugin(const QString& mess) const = 0;
};

Q_DECLARE_INTERFACE(InterfaceForPlugin,"test interface")

#endif // IPLUGIN_H
