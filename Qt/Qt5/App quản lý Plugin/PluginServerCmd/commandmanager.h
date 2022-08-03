#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include <QDebug>
#include <QMetaEnum>
#include <commandrequest.h>
#include <pluginmanager.h>

class CommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CommandManager(QObject *parent = nullptr);

    enum Commands
    {
        INSTALL,
        LIST,
        RUNALL,
        CLOSE,
        UNINSTALL
    };
    Q_ENUM(Commands)
    //Ở phiên bản mới họ dùng marco Q_ENUM ở sau khai báo enum chứ k dùng Q_ENUMS(<tên enum>) ở đầu class như trc nx
    //Nhớ phải khai báo enum thì mới dùng đc QMetaEnum nếu k chỉ dùng đc bth thôi

    void doInstall(CommandRequest command);
    void doList(CommandRequest command);
    void doDefault();
    void doRunAll(CommandRequest command);
    void doClose(CommandRequest command);
    void doUninstall(CommandRequest command);
signals:
    void responseToClient(QString);
public slots:
    void handleCommand(CommandRequest commandToHandle);
private:
    QString command;
    PluginManager *pluginManager;
};

#endif // COMMANDMANAGER_H
