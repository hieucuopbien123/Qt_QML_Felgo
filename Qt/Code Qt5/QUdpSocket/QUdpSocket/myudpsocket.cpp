#include "myudpsocket.h"

MyUdpSocket::MyUdpSocket()
{
    this->bind(QHostAddress::LocalHost,6000);
    connect(this,SIGNAL(readyRead()),this,SLOT(readyRead()));

    //tạo QUdpSocket là biến thành viên or lớp mẹ cx ok
    //QUdpSocket ez hơn QTcpSocket nhiều, nó k yêu cầu phải kết nối thành công, cứ gửi bừa dữ liệu qua ip/port nào đó
}

void MyUdpSocket::sendMess()
{
//    this->connectToHost(QHostAddress::LocalHost,6000);
//    this->write("Fuck");
    this->writeDatagram("Hello from the other side",QHostAddress::LocalHost,6000);
    //hàm write cx send đc như writeDatagram. Hàm writeDatagram k dùng đc khi QUdpSocket đã kết nối-> dùng write thay thế
    //cả 2 đều ghi luôn vào socket mà nó gửi(k ghi nội dung vào chính nó đâu nhé).
    //Nhưng Udp socket sẽ tự lưu thành pending datagram
    //Nếu dùng write, read của device thì phải connectToHost trc
    //cả hai hàm chỉ gửi chứ k ghi gì hết, chỉ gửi nd đi
}

void MyUdpSocket::readyRead()
{
    QByteArray buffer;
    buffer.resize(this->pendingDatagramSize());// để đọc toàn bộ vừa khít
    quint16 port=0;
    QHostAddress host;

    if(this->hasPendingDatagrams())
    this->readDatagram(buffer.data(),buffer.size(),&host,&port);//data chuyển từ QByteArray thành const char
    //khi nó là 1 cái server thì nó sẽ listen ở port nào đó, còn nó là client thì khi ta dùng lệnh viết vào server nào thì
    //hệ thống tự động gán 1 cổng trống trên máy cho cái client đó để gửi cho cái server
    //luồng: ta tạo ra biến server lắng nghe (bind) ở cổng 6000, ta tạo client cx v nhưng client lắng nghe ở đó kqtr->r
    //client gửi thống qua cổng đc cấp bất kỳ cho server bằng lệnh writeDatagram->server lắng nghe nó ở cổng 6000-> hàm
    //writeDatagram sẽ k phát ra readyRead (đã biết)-> server nhận phát ra readyRead->hàm readDatagram của server sẽ in
    //ra nội dung mà nó nhận đc kèm địa chỉ và ip của máy gửi

    qDebug() << "Port: " << port;
    qDebug() << "Ip: " << host;
    qDebug() << "Mess: " << buffer;//tương đương buffer.data() do qDebug tự hiểu nhưng buffer.data() ms là chuẩn
}

//host khi debug sẽ ra địa chỉ ip nhé.
//writeDatagram của QUdpSocket kp ghi nội dung cho socket mà là gửi nội dung đi đến server luôn
//readDatagram sẽ là đọc nội dung được gửi đến cái UDP Socket này=> chung quy lại cũng chỉ có readDatagram/writeDatagram
