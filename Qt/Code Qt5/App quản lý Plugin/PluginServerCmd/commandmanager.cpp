#include "commandmanager.h"
#include <QTcpSocket>

CommandManager::CommandManager(QObject *parent) : QObject(parent)
{
    pluginManager = new PluginManager(this);
    connect(pluginManager,SIGNAL(pluginResponse(QString)),this,SIGNAL(responseToClient(QString)));
}

void CommandManager::handleCommand(CommandRequest fullCommand)
{
    qDebug() << "Command Entered begin: " << fullCommand.command;

    command = fullCommand.command.toUpper().simplified();
    if(command.isEmpty())
    {
        qDebug() << "No Command Input";
    }

    //  QMetaEnum metaEnum = this->staticMetaObject.enumerator(this->staticMetaObject.indexOfEnumerator("Commands"));
    //Ở phiên bản cũ dùng Q_ENUMS thì muốn lấy metaEnum phải lấy index vất vả như v nhưng bh dùng Q_ENUM+fromType luôn
    QMetaEnum metaEnum = QMetaEnum::fromType<Commands>();
    int valOfCommand = metaEnum.keysToValue(command.toLatin1());
    //Nếu khai báo kiểu Commands thì nhớ rằng enum k đc dùng số or ký tự mà phải dùng chay key of enum. VD: =INSTALL

    //câu lệnh switch case k nhận kiểu chuỗi or list nên ta phải dùng enum
    switch(valOfCommand)
    {
    case INSTALL:
        doInstall(fullCommand);
        break;
    case LIST:
        doList(fullCommand);
        break;
    case RUNALL:
        doRunAll(fullCommand);
        break;
    case CLOSE:
        doClose(fullCommand);
        break;
    case UNINSTALL:
        doUninstall(fullCommand);
        break;
    default:
        doDefault();
        break;
    }
}

void CommandManager::doInstall(CommandRequest fullCommand)
{
    if(fullCommand.args.count() > 0)
    pluginManager->install(fullCommand.args.at(0).simplified());
    else
        doDefault();
}

void CommandManager::doList(CommandRequest fullCommand)
{
    pluginManager->list();
}

void CommandManager::doDefault()
{
    QString instruction;
    instruction.append("Enter commands like LIST, RUNALL, INSTALL <filename>,UNINSTALL <filename>, CLOSE\n\r");
    emit responseToClient(instruction);
}

void CommandManager::doRunAll(CommandRequest command)
{
    pluginManager->runAll();
}

void CommandManager::doClose(CommandRequest command)
{
    doUninstall(command);
    emit responseToClient("Goodbye");
}

void CommandManager::doUninstall(CommandRequest command)
{
    if(command.args.count() > 0)
    pluginManager->uninstall(command.args.at(0).simplified());
}


