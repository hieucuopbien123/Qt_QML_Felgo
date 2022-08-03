#include "myrunnable.h"
#include <QEventLoop>

myRunnable::myRunnable()
{
//    socket = new QTcpSocket();//lỗi 2
    QTcpSocket* socket3 = new QTcpSocket();
    qDebug() << "h" << socket3->thread();
}

void myRunnable::run()
{
    socket=new QTcpSocket();//con trỏ hay biến tùy thôi, ta thấy socket có vẻ là một thành phần của task nên khai báo tv
    if(!socket->setSocketDescriptor(socketDescriptor))//cái socket descriptor là ! của mọi QTcpSocket-> cứ gán vô là thành
        //cái socket đó thôi
    {
        qDebug() << "Socket descriptor fail!";
    }
    socket->write("Hello World!");//chú ý hàm write k nhận QString mà QByteArray or const char*
    socket->flush();
    socket->waitForBytesWritten();

    qDebug() << socket->thread();

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    //cụ thể nó nói là thế này: ta tính từ lúc chưa dùng đến cái thread hay threadpool+runnable gì cả thì ta dựa vào
    //incomingConnection vẫn có thể tạo ra 2 kết nối. Và hai kết nối này write vào liên tục và signal readyRead liên tục
    //đc phát ra thì ok-> tuy nhiên nó là synchronous(cái cách này chính là cách ta bảo k cần dùng thread mà là 2 biến
    //tcpSocket k bị xóa ở 1 class riêng đó). Synchronous ở TH đó tức là nó đang chỉ chạy 1 thread và đồng bộ=> qtr: nó sẽ
    //chạy qua cái connect readyRead này và gửi hàm connect này vào trong main thread->r chạy như bth. Điều này có thẻ dẫn
    //đến deadlock do hai hàm này bị kẹt ở cùng chỗ này vì k thể thực hiện do Qt::DirectConnection nên nếu cùng phát signal
    //cùng lúc thì main thread k thể chạy 2 cái đc. Xong nó bảo fix bằng mutex để k bị cái này chạy cái kia đứng yên vô lý.
    //Khắc phục bằng vc tạo ra QThreadPool::globalInstance()->start(...) và dùng Qt::QueuedConnection thì slot sẽ nhét
    //vào hàng chờ và thực hiện multithread asynchronous vs pool đó=> ý nó là vc ta dùng threadpool để xử lý như v nó đã
    //là asynchornous rồi, và asynchronous thì tự động tránh deadlock k cần mutex nx->hơi vô lý
    //(deadlock là do cái này và cái kia cùng truy xuất vào 1 biến, asynchronous sẽ khiến cho gặp biến mà k thể đi tiếp
    //thì exec cái khác trong lúc chờ biến exec xong ms quay lại, là tối ưu nhất)
    //=> nch là cái này có khác quái gì ban đầu đâu, chỉ là ta k rõ synchronous hay asynchronous mà thôi. Nhưng vs các
    //trình hiện đại bh khả năng là tự động asynchronous đúng như nó nói
    //=>dùng thread: multi thread asynchrnonous tốt nhất vs incoming connection=> cứ incomingConnection là đi vs thread nhé,
    //còn k dùng thread thì là có thứ tự với nextPendingConnection. Chứ đừng dùng incomingConnection k thread thì giống nextPen

    //thật ra queue và direct nó chỉ specific là direct thì thread của emitter sẽ thực hiện slot còn queue thì receiver sẽ thực
    //hiện slot, khi nào quay về thread of receiver ms thực hiện chứ kp thực hiện ngay hay j.
    //4 TH: dùng nextpend,dùng incoming,dùng incoming vs thread,dùng incoming vs pool;1)mỗi cái đều có 1 thread và bth là lập
    //trình chỉ có 1 thread hđ tức là đang là main thì sẽ thread của cái khác và quay lại main-> đó là lập trình đơn luồng
    //k đồng bộ(lập trình đơn luông đồng bộ k còn trong thực tế, vì bh k thể thực hiện 1 cái r ms sang cái khác vì thực hiện 1
    //task bh cx kèm với hoàn thành task khác thì ms tiếp tục đc)->ở TH này là lập trình đơn luồng k đồng bộ-> tức là thực hiện
    //cj đi chăng nx cx chỉ có 1 thread->đang ở cái telnet này sang cái telnet khác thì gửi vào mainthread thực hiện;2)dùng
    //incoming vs 2 telnet khác nhau mà k đi vs thread=>nó tương tự như nextPend. Cái này có thể gây deadlock ở phía ng dùng
    //vì bth đơn luồng ta tạo dù trùng nó cx chờ xong ms thực hiện nhưng nếu Th này 2 ng dùng cùng kết nối vs server 1 lúc(giả
    //thiết 2 biến con trỏ khác nhau chứ k mất signal) thì gây deadlock do k rõ cần nhét cj vào mainthread;3)nhưng incoming khác
    //nextPend là có thể dùng vs thread->khi đó các connection đều là độc lập và 2 ng có thể trao đổi cùng lúc->đó là lập trình
    //đa luồng đồng bộ vì mỗi connection chỉ thực hiện 1 nhiệm vụ từng ng chứ kp đang làm ng này nhảy sang làm ng khác->nguy cơ
    //deadlock vẫn còn, giả sử có 1 biến server mà 2 ô cùng truy cập thì toang có thể tránh bằng mutex;4)lập trình đa luồng bất
    //đồng bộ tránh đc deadlock: ví dụ ở 3), thread a và b cùng truy cập vào 1 biến nhưng do đồng bộ nên cả 2 k thể dừng lại
    //nhưng nếu dùng QRunnable thì k cần mutex nx->vd a và b cùng truy cập biến c thì a thực hiện sau đo thread đang thực hiện
    //b sẽ k dừng lại mà thực hiện 1 cái d nào khác khi a truy cập c xong thì b ms truy cập c->máy sẽ tự động tính toán hết và
    //các thread sẽ kp dừng lại để chờ mà exec cái khác

    //ở đây như này là chưa đủ vì k có hàm exec tức là chạy hàm run phát là runnable phát signal xóa luôn-> chưa kịp disconnected
    //nx-> xóa r thì các signal slot cx mất nên tắt đi cx k xóa->dung eventLoop trong thread là ổn nhất->tạo ra hàm exec dù class
    //k có exec, lại k sợ các hàm khác mất chức năng do ở trong threadPool độc lập asynchronous
    QEventLoop loop;
    connect(socket,SIGNAL(disconnected()),&loop,SLOT(quit()));
    loop.exec();
}

void myRunnable::readyRead()
{
    qDebug() << "Data: " << socket->readAll();
    QTcpSocket* socket2 = new QTcpSocket();
    qDebug() << "socket2:" << socket2->thread();
    qDebug() << "socket:" << socket->thread();
    socket->write("test");
}

void myRunnable::disconnected()
{
    qDebug() << socketDescriptor << " disconnected";
    socket->deleteLater();
//    exit(0);//exit ở đây thì khi socket k kết nối nx sẽ khiên Ct tắt luôn
    //vì cái exit này là exit cái event loop ở main mà tránh nhầm. Cái loop kia là biến cục bộ ta k thể loop->exit ở đây đc
    //Ta đặt điều kiện disconnection thì kết thúc cái loop kia r thì cần gì exit nx. Nếu k có connect exit thì eventloop
    //phải là con trỏ thành viên của class và loop->exit ở đây để kết thúc
}
//nếu có nhiều hơn max sẽ chờ ở hàng đợi cho đến khi có thread free=> 1 connection 1 thread
