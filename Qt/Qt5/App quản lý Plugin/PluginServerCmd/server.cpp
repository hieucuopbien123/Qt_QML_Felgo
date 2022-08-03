#include "server.h"

server::server()
{
    commandManager = new CommandManager(this);
}

void server::startServer(int port)
{
    if(!listen(QHostAddress::Any,port))
    {
        qDebug() << "Couldn't start server: " << this->errorString();
        return;
    }
    else
    {
        qDebug() << "Server is listening";//nên viết ra từng bước
    }
}

void server::incomingConnection(qintptr socketDescriptor)
{
    RunnableTask* task = new RunnableTask();
    task->setAutoDelete(true);//k lo xóa biến task ở đây nx
    task->socketDesciptor = socketDescriptor;

    connect(task,SIGNAL(commandComing(CommandRequest)),commandManager,SLOT(handleCommand(CommandRequest)),Qt::DirectConnection);
    connect(commandManager,SIGNAL(responseToClient(QString)),task,SLOT(sendResponse(QString)));

    QThreadPool::globalInstance()->setMaxThreadCount(5);
    QThreadPool::globalInstance()->start(task);
}


