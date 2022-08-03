#include "myserver.h"

myServer::myServer(QObject *parent) : QTcpServer(parent)
{

}

void myServer::startServer()
{
    if(!this->listen(QHostAddress::Any,1235))
    {
        qDebug() << "could not start server: " << this->errorString() << this->serverError();
    }
    else
    {
        qDebug() << "Listening...";
    }
}

void myServer::incomingConnection(qintptr socketDescriptor)//qintptr is pointer to singed int
{
    myThread* thread=new myThread(socketDescriptor);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}

//Nếu dùng nextPendingEvent cx ok nhưng sẽ k độc lập mà thao tác theo thứ tự. Ví dụ dùng connect là toang. Còn hàm trên là
//chuyên dùng cho multi
//Luồng: tạo server+listen=>incomingConnection khai báo thread-> dùng QTcpSocket setSocketDescriptor với cái incoming
//=>thao tác với socket=> xóa và đóng
//=>nên nhớ là exec() cái thread nếu muôn vô tận, mà thread lại độc lập=>ta có nhiều client telnet kết nối cùng lúc và thao
//tác đc. VD: hiện cửa sổ ta cũng phải làm cho nó vô tận khi dùng nv vì tắt là ta tự thao tác bằng chuột mà
