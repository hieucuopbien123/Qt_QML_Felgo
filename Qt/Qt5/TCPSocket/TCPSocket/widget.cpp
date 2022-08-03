#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    tcpSocket=new QTcpSocket(this);//cx là 1 lớp con của QIODevice->kiểm lỗi, đọc ,ghi ,..

    //lấy quá trình truyền tin(ng ta thg dùng signal trùng vs slot nv để yêu cầu làm gì vs tất cả các signal phát ra)
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(tcpSocket,&QTcpSocket::errorOccurred,this,&Widget::errorOccurred);
    connect(tcpSocket,&QTcpSocket::hostFound,this,&Widget::hostFound);
    connect(tcpSocket,&QTcpSocket::proxyAuthenticationRequired,this,&Widget::proxyAuthenticationRequired);
    connect(tcpSocket,&QTcpSocket::stateChanged,this,&Widget::stateChanged);

    tcpSocket->connectToHost("www.google.com",80);
    tcpSocket->waitForConnected(3000);//chờ k đủ mà thực hiện tiếp luôn sẽ error

    //carriage return: về đầu dòng \r; line feed: bắt đầu dòng mới \n=>hàm write của QIODevice là ghi vào trong device, vs
    //tcp socket sau khi kết nối vs host r thì hàm write sẽ gửi request GET bằng HTTP cho server có nội dung là cái này. Ta
    //cần gửi bad request nên cứ viết bừa cj vào và thêm \n \t ở cuối. Bởi vì request của http khi gửi sẽ có cấu trúc là
    //kết thúc bằng 2 carriage return and line feeds nên ta cứ viết thêm vài cái cho đúng. Có như v thì nó mới hiểu cái
    //write của ta là gửi request, nếu k đúng cấu trúc thì sẽ k gửi cj và k đọc đc cj cả, ok thì đọc lỗi 400
    tcpSocket->write("Hello World\r\n\r\r\n\n");//toàn bộ kq lưu hết vào biến device, banner grab và file html of trang
    //nó gửi request cho server và nếu server gửi lại cho nó cj thì lưu vào socket, k thì k lưu gì cả
    tcpSocket->waitForBytesWritten(3000);
    tcpSocket->waitForReadyRead(3000);//cả 3 hàm wait đều trả về GT có tcong hay k

    ui->textEdit->append(QString::number(tcpSocket->bytesAvailable()));//lưu byte là qint chính là qlonglong lấy đc
    ui->textEdit->append(tcpSocket->readAll());

    //cái server chứa website phải k bật firewall mà block cái request thì ms đc
    //Qtr: tạo TCPSocket-> connect nó với host server->write là xong=> nhớ wait ở từng bước chứ k đc thực hiện lt

    tcpSocket->close();//đóng+disconnect
}
void Widget::connected()
{
    ui->textEdit->append("\nConnected");
}
void Widget::disconnected()
{
    ui->textEdit->append("\nDisconnected");
}
void Widget::errorOccurred(QAbstractSocket::SocketError socketError)
{
    ui->textEdit->append(QString("\nSocket Error: ")+QString::number(socketError));
}
void Widget::hostFound()
{
    ui->textEdit->append("\nHostFound");
}
void Widget::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    ui->textEdit->append("\nProxyAuthenticationRequiredd");//QNetworkProxy cung thao tác làm vc vs proxy
    //QAuthenticator cung cấp 1 object lưu các thứ dùng để xác thực như password
    //cái signal này phát ra khi 1 cái proxy cần authenticator sử dụng.authenticator có thể đc điền vào thông tin để xác
    //thực và tiếp tục connect-> lấy thông tin ra làm gì đó...
}
void Widget::stateChanged(QAbstractSocket::SocketState socketState)
{
    ui->textEdit->append(QString("\nStateChanged: ")+QString::number(socketState));
    //k đc dùng QString(int) mà là QString::number(int) vì nó sẽ đổi từ số sang ký tự ASCII mất
}
