#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class myThread : public QThread
{
    Q_OBJECT
public:
    myThread(int id);
    void run();
signals:
    void error(QTcpSocket::SocketError);
public slots:
    void readyRead();
    void disconnected();
private:
    QTcpSocket* socket;
    int socketDescriptor;
};

#endif // MYTHREAD_H
