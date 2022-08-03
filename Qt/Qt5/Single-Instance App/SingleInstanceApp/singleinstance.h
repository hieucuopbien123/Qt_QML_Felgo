#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include <QObject>
#include <QDebug>
#include <QLocalServer>
#include <QLocalSocket>
//QLocalSocket là 1 named pipe trong window còn trong linux nó như 1 socket bth
//QLocalServer là cái chờ kết nối từ QLocalSocket
//QLocalSocket k kế thừa QAbstractSocket,nó k thực là 1 network socket(k có network address,k có hàm in địa chỉ) mà là
//named pipe trong win nên có thể giao tiếp với các máy tính win trong network bằng 1 cái tên string. QTcpSocket là 1
//network socket có network address. QLocalSocket vẫn kế thừa IODevice nên vẫn có đọc ghi

class SingleInstance : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstance(QObject *parent = nullptr);
    ~SingleInstance();

    void listen(QString name);
    /**
     * @brief Check whether the previous window exists
     * @param name
     * @param args
     * @return
     */
    bool checkPreviousWindow(QString name, QStringList args);

public slots:
    void newConnection();
    void handleReadyData();

signals:

private:
    QLocalServer server;
    QLocalSocket* socket;

};

#endif // SINGLEINSTANCE_H
