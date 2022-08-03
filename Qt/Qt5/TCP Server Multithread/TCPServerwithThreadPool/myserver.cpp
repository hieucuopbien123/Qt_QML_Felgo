#include "myserver.h"

MyServer::MyServer()
{
    pool=new QThreadPool(this);
    pool->setMaxThreadCount(2);
    qDebug() << "mainthread: " << this->thread();
}

void MyServer::startServer()
{
    if(this->listen(QHostAddress::Any,12345))
    {
        qDebug() << "Server Connected!";
    }
    else
    {
        qDebug() << "Cannot connect!" << this->errorString();
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    myRunnable* task=new myRunnable();
    task->setAutoDelete(true);
    task->setObjectName(QString::number(socketDescriptor));

    task->socketDescriptor=socketDescriptor;

    pool->start(task);
//    task->moveToThread(this->thread());//k hoạt động, chuyện j xảy ra
//    QThreadPool::globalInstance()->setMaxThreadCount(15);
//    QThreadPool::globalInstance()->start(task,0);
    //ở trong Qt có sẵn 1 instance là 1 biến threadPool r-> ta dùng luôn or tự tạo riêng như ở trên.
}
//cách dùng threadPool: khai báo pool và số lượng max thread-> khai báo class kế thừa QRunnable và thao tác class trong
//hàm run->tạo biến class kế thừa QRunnable->pool start nó là xong
//Lưu ý: xóa biến sau khi sử dụng với autodelete
