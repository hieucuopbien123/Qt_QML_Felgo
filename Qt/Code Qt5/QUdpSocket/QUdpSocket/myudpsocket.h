#ifndef MYUDPSOCKET_H
#define MYUDPSOCKET_H

#include <QUdpSocket>

class MyUdpSocket : public QUdpSocket
{
    Q_OBJECT
public:
    MyUdpSocket();
    void sendMess();
public slots:
    void readyRead();
};

#endif // MYUDPSOCKET_H
