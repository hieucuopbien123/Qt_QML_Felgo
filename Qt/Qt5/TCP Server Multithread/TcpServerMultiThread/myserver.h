#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include <mythread.h>

class myServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit myServer(QObject *parent = nullptr);
    void startServer();
signals:

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    //dùng độc lập thì dùng incomingConnection
};

#endif // MYSERVER_H
