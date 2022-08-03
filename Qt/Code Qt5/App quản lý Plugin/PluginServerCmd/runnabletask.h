#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H

#include <QRunnable>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QEventLoop>
#include <commandrequest.h>

class RunnableTask : public QObject,public QRunnable
{
    Q_OBJECT
public:
    RunnableTask();
    void run();//nếu k khai báo hàm run ngay khi tạo class thì sẽ k dùng được kiểu biến này ở nơi khác
    int socketDesciptor;
public slots:
    void handleReadyRead();
    void handleDisconnected();
    void sendResponse(QString response);
    void getError(QAbstractSocket::SocketError);
signals:
    void commandComing(CommandRequest command);
    void sendResponseTask(QString response);
private:
    QTcpSocket* socket;
    QString commandBuffer;
};

#endif // RUNNABLETASK_H
