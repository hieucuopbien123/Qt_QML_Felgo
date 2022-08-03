#include "mythread.h"

myThread::myThread(int id)
{
    socketDescriptor=id;
}

void myThread::run()
{
    qDebug() << socketDescriptor << " starting thread";
    socket=new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());//quên chưa bắt error->nên để như thế này và viết 1 hàm error riêng
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    //QDirectConnection sẽ thực hiện lệnh đó ngay lập tức, còn QueuedConnection sẽ nhét vào hàng chờ của thread này, cái
    //nào nhét vào queue trc thực hiện trc nhết vào sau thực hiện sau, nên specific khi dùng connect vs thread

    exec();//cái thread này exec tức là cái socket của server (incoming) sẽ tiếp tục hoạt động
    //nếu k có exec() tức là hàm run chạy tơi đây là kết thúc và thread gọi finished(). Như ta đã khai báo thread finished
    //thì nó sẽ bị xóa deleteLater. Nó bị xóa thì biến socket desciptor cx bị xóa theo mà còn chưa disconnected luôn. Ta
    //gọi exec() thì sẽ đưa vào vòng lặp và run chạy đến khi nào ta disconnected socket thì ms gọi hàm exit kết thúc->xóa
    //chú ý thứ tự xóa, disconnected ms xóa nhé(sai vì xóa thì nó tự động disconnect chứ)
}

void myThread::readyRead()
{
    QByteArray data=socket->readAll();
    qDebug() << "Data in: " << data;
    socket->write(data);//bật telnet và ghi vào nó sẽ hiện double do write nên gửi trả từ server về telnet đo
    //tư duy rằng đây chính là server và ta đang gửi cho client chứ đừng nhầm
}

void myThread::disconnected()
{
    qDebug() << socketDescriptor << " disconnected";
    socket->deleteLater();//disconnected thì close r
    exit(0);
}
