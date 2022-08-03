#include "pluginitem.h"

PluginItem::PluginItem(QObject *parent) : QObject(parent)
{
    loader = nullptr;
    interface = nullptr;
}

PluginItem::PluginItem(QPluginLoader *loader, InterfaceForPlugin *interface, QObject *parent)
{
    this->loader = loader;
    this->interface = interface;
    filename = loader->fileName();
}

QString PluginItem::getName()
{
    return filename;
}
