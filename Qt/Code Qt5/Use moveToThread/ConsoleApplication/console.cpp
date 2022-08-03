#include "console.h"
#include <QDebug>

Console::Console(QObject *parent) : QObject(parent)
{
    qDebug() << this->thread();
    moveToThread(&myThread);
    //bản thân biến myThread nằm trong main thread và lưu 1 thread khác-> moveToThread cho nó thì move cái hiện tại vào cái
    //thread mà nó lưu. Hàm move ở đây là k cần thiết vì chỉ cần connect là cái bên dưới là hàm thực hiện độc lập r
    qDebug() << this->thread();//chỉ cần như này là sang luôn 1 thread độc lập r. connect signal slot thread start nx thôi

    connect(&myThread,SIGNAL(started()),this,SLOT(getText()));
    connect(this,SIGNAL(textAvailable(QString)),this,SLOT(printText(QString)));
//    connect(this,SIGNAL(destroyed()),&myThread,SLOT(deleteLater()));//thừa vì nó là thành viên sẽ tự bị xóa
    myThread.start();
}

void Console::getText()
{
    QTextStream inStream(stdin);
    QString content;//như này tránh leak khi gọi while vô hạn thì tạo vô số content sẽ quá nh trong stack
    //thật ra điều này còn tùy vào yêu cầu sử dụng. Vì chả có ai dùng cmd gõ vài ngàn dòng cả. Nhưng tester sẽ phàn nàn
    while(1)//dùng while ở đây tránh tạo memory leak biến instream lưu quá nhiều full stack
    {
        content = inStream.readLine();
        emit textAvailable(content);
    }
    //ta muốn cmd gọi hàm này nhiều lần vì k thể nhập phát là xong luôn đc mà phải nhập liên tiếp
    //getText();//giả sử dùng như này.Cx ok nhưng có 1 nhược điểm là thread sẽ không bao giờ kết thúc. Nếu dùng quit() hay exit
    //cho thread thì k đc vì nó là các hàm kết thúc loop của thread tức là hàm protected exec của nó nhưng ở đây ta k dùng
    //Tuy nhiên vấn đề đó k đáng lo vì thread này độc lập, giả sử tạo nhiều console, khi tắt 1 cửa sổ console di thì myThread
    //là biến thành viên cx tự bị xóa nên chả sao. Vấn đề đáng lo hơn là loop này gọi liên tục thì biến inStream trong Stack
    //k bị xóa vì kbh thoát đc hàm getText. Giả sử ta dùng hàm này 1 triệu lần thì sẽ có 1 triệu biến cục bộ inStream lưu
    //trong stack=> đơn giản nhét nó là thành phần của class or nhét ra ngoài vòng while là xong. Có nhiều cách fix.
    //Lúc này ta chỉ còn 1 trở ngại là cái vòng lặp sẽ kbh kết thúc và biến myThread k bị xóa. Ở Th này k đáng lo vì vai trò
    //của console chỉ có mỗi thế là nhập vào r in ra. Nếu chẳng may có cần gì khác thì thêm điều kiện dừng vòng while là xong
    //or muốn kết thúc thread mà k xóa biến this->dừng vòng while là kết thúc hết=>có éo j khó đâu. Ví dụ gõ exit thì end
    //điều quan trọng là khi làm cj, thì hãy nghĩ rằng nó có thể làm 1 triệu lần chẳng hạn, để ý xem liệu có memory leak
}

void Console::printText(QString content)
{
    QTextStream outStream(stdout);
    outStream << "Content: " << content << "\n";
}

//Khi tạo console ta k nên nghĩ chật hẹp là 1 màn hình 1 cái mà có thể nó chỉ là 1 thứ rất nhỏ trong 1 tổng thể. Giả sử ta có
//1 app GUI có 1 nút bấm, cứ bấm thì 1 màn hình console hiện ra, gõ vào màn hình thì làm gì với Ct GUI bằng signal,slot.

//Ta cần đưa vào thread vì muốn nó độc lập, giả sử có 2 cửa sổ console 1 CT thì ta muốn 2 cửa đó độc lập chẳng hạn. Mỗi cmd ta
//phải đưa vào loop vô tận để thực hiện lệnh, khi đó ta cũng k muốn các thứ khác bị dừng lại để cho mình cmd chạy=> khi có
//những thứ thao tác độc lập nhau thì nên dùng thread độc lập. VD này đưa ta hướng nhét vào 1 thread độc lập rất ez.

//Để lấy hay in ta có thể dùng QTextStream là chuẩn nhất. qDebug() cx là in nhưng nó dùng để debug chứ k nên dùng trong app.
