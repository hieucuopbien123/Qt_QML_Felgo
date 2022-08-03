#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include "runnabletask.h"
#include <QThreadPool>
#include <commandmanager.h>

class server : public QTcpServer
{
    Q_OBJECT
public:
    server();
    void startServer(int port);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
   CommandManager* commandManager;
};

#endif // SERVER_H
