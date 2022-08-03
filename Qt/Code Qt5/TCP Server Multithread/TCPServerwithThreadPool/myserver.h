#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QThreadPool>
#include "myrunnable.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    MyServer();
    void startServer();
protected :
    void incomingConnection(qintptr socketDescriptor) override;
private:
    QThreadPool* pool;
};

#endif // MYSERVER_H
