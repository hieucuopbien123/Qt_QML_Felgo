#include <QCoreApplication>
#include "myudpsocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyUdpSocket server;
    MyUdpSocket client;
    client.sendMess();//cả client và server đều bắt ở cổng 6000 nhưng một cổng chỉ đc 1 chức năng nên chỉ hiện 1 lần server nhận
    //nó làm server nhận cx đc luôn
    return a.exec();
}
