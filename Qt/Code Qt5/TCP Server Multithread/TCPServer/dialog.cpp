#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    server=new QTcpServer(this);
    if(!server->listen(QHostAddress::Any,5999))
    ui->textEdit->setText("Cannot connect");

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    server->waitForNewConnection(0);//chờ ít nhất 0ms để nó bị kết nối-> đây là block func, chờ ms thực hiện tiếp bên dưới
    //nếu -1 thì sẽ chạy mãi mãi k show đc luôn-> hàm này dùng ở dây là vô dụng
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::newConnection()
{
    QTcpSocket* tcpSocket=server->nextPendingConnection();

    tcpSocket->write("Hello world!!");
    tcpSocket->flush();//QIODevice luôn

    tcpSocket->waitForReadyRead(3000);

    ui->textEdit->append(QString::number(tcpSocket->localPort())+" "+QString::number(tcpSocket->peerPort()));
    //in port của server kết nối với socket và port của cái socket này. peer là cái đang ghép nối với đó
    ui->textEdit->append(tcpSocket->localAddress().toString() + " " + tcpSocket->peerAddress().toString());
    //địa chỉ host và địa chỉ của socket này

//    tcpSocket->close();
//    tcpSocket->deleteLater();
}

//hiểu sai bản chất: Khi server và client kết nối với nhau, mỗi bên tạo ra 1 socket để trao đổi ở giữa app và transport.
//server chỉ có 1 cổng để trao đổi nhưng lại có thể tạo ra nh socket ứng với mỗi client, socket này là của server và sẽ
//là kênh trao đổi riêng vs client đó-> vc ta ghi dữ liệu vào server thực ra là ghi vào cái socket đó. Vâng socket đó
//là nextPendingConnection(); do đó ta tạo ra nh client ghi vào server xong lại tạo tiếp client khác lấy nội dung server
//nhưng k thấy nội dung gì vì nó đang trao đổi vs socket mới đc tạo ra. Còn incoming chỉ dùng cho multiThread. Bản chất
//hàm write của nextPendingConnection là ghi mẹ vào socket của client luôn từ socket của server, do
//đó nó k phát signal readyRead(write thì k phát mà thêm từ chỗ khác ms phát). Telnet thì cửa sổ ta dùng lệnh thao tác để
//tạo ra 1 client gửi yêu cầu tới server. Ta gửi lệnh open thì máy sẽ gán 1 cổng bất kỳ cho telnet làm client gửi qua đó
//đến cổng và ip của server, client tạo 1 socket ngay dưới lớp app r. Server tạo ra 1 socket trống và ghi nội dung vào
//đó và 2 cái socket trao đổi cho nhau. Nội dung socket server gửi qua cho socket client nên ta nhìn thấy. Nv cái nội
//dung trên telnet ta thấy là client r. Ta gõ lệnh vào đó thì nó gửi qua socket client->port client->port server->socket
//server nhận phát readyRead(chứ write thì k phát). Nên nhớ là telnet đúng là ta ghi vào nội dung của client gửi tới
//server nhưng chỉ server phát readyRead chứ client k phát nếu ta kt đc vì chỉ phát khi nhận đc dữ liệu từ bên ngoài tới.

//update vẫn hiểu sai: ta cần hiểu lại write và telnet-> hàm write của 1 IODevice cho phép ta ghi vào trong cái iodevice
//đó, nhưng nếu cái iodevice đó đang kết nối với một cái socket khác thì hàm này sẽ thành hàm gửi data cho cái socket mà
//nó đang kết nối(là hàm gửi đi chứ kp nhận vào và k phát signal readyRead j hết)-> cho nên là tạo ra một socket client
//kết nối vs server thì write của socket client sẽ gửi data đến cho server, còn write của socket server sẽ gửi data đến
//cho client.(nếu socket kết nối vs server website thì vc gửi từ socket client sẽ thành gửi request GET thì hàm write
//cx ghi vào socket của server web nhưng phải đúng cú pháp \r\n, nội dung k đúng thành bad request)=> mở telnet lên thì
//nextpendingconnection ở phía server write("hello world") vào client nên open ta thấy đc nội dung của client có hello
//world. Còn telnet về sau ta gõ nội dung thì đó tương ứng lệnh write của client gửi tới socket server v. 2 client cùng
//kết nối server mà đều trống k là ta đã giải thích bên trên. tất cả đều là gửi để ghi data chứ kp gửi lệnh đâu, ví dụ
//gửi lệnh get cho internet thì nó tự hiểu là lệnh open chứ nội dung ta ghi đó kp là lệnh.

//Như v thì ta hoàn toàn có thể lấy nội dung mà server nhận đc vs Udp thì readDatagram còn tcp là nextPendingConnection.
//Nếu ta dùng writeDatagarm, thì là gửi đến server nhưng thực chất cx chỉ là viết vào socket của server như write.
//Chỉ là write thì k xác định đích nên phải kết nối từ trc r thôi.

//Cái cửa sổ gõ lệnh của telnet là cửa sổ giúp ta gửi dữ liệu tới server nào đó thông qua commandPrompt. Cửa sổ đó
//đóng VT là 1 client giao tiếp với server ta dùng lệnh=> lệnh open là lệnh gửi yêu cầu tới server cho phép mở và xem
//nội dung bên trong server. Khi ta tự tạo server trống như này thì socket server chả có gì nên hiện blank còn web thì 404

//Màn hình về sau của telnet sau khi open chính là cái màn hình của client đã nhận nội dung của server(giả sử là
//server ta tự tạo trống chả có gì hết).

//Khi ta viết nội dung vào client trong telnet thì client gửi sang cho server nội dung đó, server giả sử có readyRead
//lại gọi write cái nội dung đó thì nó viết lại vào client, client lại nhận đc nên ms thấy ký tự bị nhân đôi
//=>Do đó nếu phát signal readyRead mà write lại bên trong thì những gì ta viết sẽ nhân đôi ký tự viết vào ở telnet

//ví dụ ở ngay file này ta mở tel net lên và kết nối với server này thì-> gõ vào telnet sau khi open là ghi từ client
//vào server,(có ghi data vào client). Còn write từ nextPendingConnection là ghi từ socket server vào client, chứ nó
//k ghi vào socket phát ra nó

//Về vấn đề signal/slot: khi ta dùng thì cái SIGNAL và SLOT phải là thành phần của cái đối số 1 và 3 hàm connect. Hàm
//SLOT của this thì chỉ đc dùng các biến thành viên của class là this, k đc dùng các biến cục bộ nhỏ trong hàm. Vc
//dùng lamba func [&] cx chỉ đc nv chứ k lợi dụng nó để dùng biên ngoài đc => ta khai báo pointer socket trong hàm.
//Lỗi: ta dùng connect đối số 3 là socket, 4 là lamba thì lỗi vì lamba ta tạo ra nó k phải là 1 hàm của socket, ta k
//thể tự thêm vào nv, ta có thể fix bằng cách tạo 1 class socket của riêng ta và tự thêm slot theo ý ta.
//Lỗi:ta dùng đối số 3 là this, đối số 4 là lamba=> thế thì k đc dùng biến socket ở trong hàm vì nó kp 1 tv của class
//=> nếu ta dùng phải nv thì sẽ gặp lỗi notResponding, mà éo báo lỗi
//Để có thể thao tác toàn vẹn với QTcpSocket trong hàm thì ta có thể tạo biến QTcpSocket là pointer tv của class. Nv
//thì signal và slot ta dùng thoải mái với socket vì nó là tv of class r, k cần tạo class riêng nx.
//Giả sử ta tạo ra 2 cái telnet cùng connect với server đó và socket là biến tv. Theo lẽ thg,ta chỉ có một biến
//socket nên biến socket sẽ lưu địa chỉ cửa sổ mới nhất còn cái cửa sổ cũ vẫn dùng đc là vì nó là cửa sổ vùng nhớ đã
//đc cấp phát và ta chưa xóa nó đi, chỉ có điều k còn biến nào trỏ đến nó cả, ta k thể thao tác với nó bằng biến
//socket qua code nx mà chỉ qua màn hình hiển thị k biến mất. Điều đó làm phát sinh lỗi connect signal slot lq đến
//cái socket, hay các signal slot của telnet cũ nó éo hoạt động nx.
//Điều này cx giống như Ct ấn 1 nút thì 1 cửa sổ hiện ra, bằng cách này thì ta hiện ra infinite cửa sổ và thao tác
//dc với toàn bộ nhưng các thao tác với connect của các cửa sổ cũ bị xóa đi nên ta chỉ nên dùng khi code đem bỏ chợ.
//=>đó là NN ta ấn cửa sổ cũ thì nó k in ra trong Debug vì nó chả chứa gì cả,ta ấn nhưng thao tác với code lưu vào
//socket k hoạt động, ta đang cố ghi vào 1 vùng nhớ đã đc cấp phát nhưng socket k trỏ đến

//Như v, ta rút ra cách hay nhất của 1 Ct trong qt, ta muốn là khi ấn một nút thì 1 cửa sổ hiện ra-> ấn nút tiếp theo
//thì cửa sổ mới hiện ra và hai cửa sổ này vẫn giữ nguyên signal, slot. Sau đó ta có thể lấy dữ liệu từ hai cửa sổ
//để dùng cho màn hình lớn ban đầu. Để làm đc điều đó thì mỗi lần ra ấn nút là nó tạo ra một biến con trỏ và biến con
//trỏ đó phải bị nhét vào vòng lặp k kết thúc trừ khi ta tự tay tắt. Để thao tác đc với signal/slot, thì cái class đó
//phải do ta tự tạo ra, ta sẽ tùy chỉnh signal/slot. Ta truyền các đối số cần thiết vào constructor để dùng dữ liệu,
//ta truyền con trỏ vào thì vào trong class đó đổi ra sao thì nó sẽ tự đổi và dùng nó ở màn hình chính luôn.
//Tuy nhiên ta cx có thể chỉ tạo ra 1 cửa sổ nhưng cửa sổ đó do ta tự tạo, nv khi dùng signal và slot trong cửa sổ đó
//thì nó vẫn hoạt động chỉ là signal slot của cái biến dialog trong cửa sổ lớn k hoạt động mà ta đâu có dùng đến nó
//=>Ta hoàn toàn có thể tùy biến ra vc khai báo ở đâu hay làm gì tùy thuộc vào mục đích ta dùng cửa sổ và lưu trữ ntn
//Điều qtr là ta tuân thủ nguyên tắc cj là thuộc tính của cj hay k và 1 hàm trong class lớn làm ht 1 chức năng

//Tùy biến: xác định vai trò từng biến và tính toán vc khai báo cho phù hợp với các tính chất sau: dữ liệu của nó đc
//lưu ntn? cái cửa sổ hiện ra ta có muốn hiện vô hạn k? Nếu ta tạo nhiều cửa sổ thì các cửa sổ cũ có thao tác vs
//signal slot nx k? Nó có là thuộc tính của class k, dùng vào các vc khác? Nó có thỏa mãn 1 hàm 1 chức năng?
//Ta đã quá ngu khi nghĩ rằng dùng thread vs run và create+start ở bất cứ chỗ nào đã là hay. Nếu ta muốn 1
//class với rất nhiều chức năng làm độc lập thì rõ ràng một hàm slot k thể nào quất đc. Ta có thể tạo ra 1 QThread
//của riêng ta, trong QThread đó ta khai báo ra các biến class cần dùng, làm tất cả trong hàm run. trong class mẹ ta tạo
//thread và start=> chỉ có các thao tác với cửa sổ trong hàm run là độc lập.
//Tùy biến vs thread: dùng create với hàm hiện cửa sổ-> cửa sổ hiện độc lập. bên trong class cửa sổ lại create các chức
//năng thì các chức năng lại độc lập nhưng rõ ràng k hay bằng cái trên vì trên giống luồng phổ biến hơn
//Lưu ý cách xóa: close các cái có thể đóng trc-> deleteLater các biến tv và biến mẹ nếu cần-> có thể kt nếu tồn tại thì
//ms xóa-> hide nếu dùng nó về sau(nếu ta khai báo new liên tục thì deleteLater luôn cx ok)

//TH infinite cửa sổ mà ấn nút class mẹ thì cửa sổ bị xóa-> nó sẽ chỉ xóa cửa sổ ms nhất-> Giả sử ta thử tùy biến ấn nút
//của class mẹ thì tất cả các infinite cửa sổ đều bị xóa=> cho các dialog vào vector và ấn thì xóa sạch vector class mẹ.
//tư duy như v vì hàm xóa là hàm của class mẹ, muốn ảnh hưởng đến dialog thì tất cả các dialog phải ở trong class mẹ nên
//nhét vào 1 vector
