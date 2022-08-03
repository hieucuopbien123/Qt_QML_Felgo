#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <pluginitem.h>
#include <QDir>
#include <IPlugin.h>

#include <bits/stl_list.h>

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = nullptr);
    void install(QString filename);
    void runAll();
    void list();
    void uninstall(QString filename);
signals:
    void pluginResponse(QString);
private:
    QList<PluginItem*> listPluginItem;
    QString path;
};

#endif // PLUGINMANAGER_H
