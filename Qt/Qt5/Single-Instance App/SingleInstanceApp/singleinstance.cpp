#include "singleinstance.h"

SingleInstance::SingleInstance(QObject *parent) : QObject(parent)
{

}

SingleInstance::~SingleInstance()
{

}

void SingleInstance::listen(QString name)
{
    qDebug() << "Server is listening...";
    server.removeServer(name);
    server.listen(name);
    connect(&server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void SingleInstance::newConnection()
{
    qDebug() << "New connection!!";
    socket = server.nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyData()));
}

void SingleInstance::handleReadyData()
{
    qDebug() << "Read: " << socket->readAll();
    socket->deleteLater();//cần gì xóa ở đây, cái socket trong cửa số mới nó là biến cục bộ sẽ tự die thôi
}

bool SingleInstance::checkPreviousWindow(QString name, QStringList args)
{
    qDebug() << "Checking for previous window!";
    QLocalSocket socket;
    socket.connectToServer(name,QLocalSocket::ReadWrite);
    if(socket.waitForConnected())
    //Hàm này sẽ trả về true nếu connect thành công và false nếu thât bại->mà connect thành công tức là server đã được
    //khởi tạo->khi đó đã có 1 instance đằng trước tạo ra rồi nên cái instance này k cần mở->return true luôn.
    {
        for(const QString &str : args)
        //vòng for này của C++11 nhanh hơn foreach và k copy container nên chỉnh sửa trực tiếp đc
        {
            socket.write(str.toLocal8Bit());
        }
        socket.waitForBytesWritten();
        //waitForBytesWritten rất quan trọng, nếu k có nó Ct chạy vào phát éo hiện j cả
        return true;
    }
    qDebug() << socket.errorString();
    return false;
}
