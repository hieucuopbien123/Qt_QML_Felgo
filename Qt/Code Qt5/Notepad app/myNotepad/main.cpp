#include "mainwindow.h"
#include <QTextCodec>
#include <QApplication>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
//    QApplication::setWindowIcon(QIcon(":/src/imgs/paste.pn"));//set icon mặc định cho window

    MainWindow w;

    /*QTextCodec *codec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(codec);
    //hàm setCodecForLocale set cho cái codec ta dùng cho locale là codec nào ta muốn-> cần khi app dùng đến công cụ
    //cần thiết cho địa lý thì sẽ tự động dịch theo codec địa lý ta set
    QString cs = codec->toUnicode(argv[1]);//hàm này sẽ chuyển đổi char* thành QString theo encode đc set
    //ta có thể dùng cái codec ta tạo để chuyển đổi const char* thành QString có unicode nhưng đểu vl*/

    if(a.arguments().size() > 1)
    {
        QString s = a.arguments().at(1);
        w.load(s);
    }
    //2 TH: mở ứng dụng thì hiện file trống nhưng mở ứng dụng dùng cho 1 file khác thì phải mở ứng dụng hiển thị file đó lên

    //đối số int argc(argument count) và char* argv[](argument vector) truyền vào hàm main, dùng khi ta cần xử lí command line
    //argument. Khi thao tác với command line ví dụ lệnh chạy CT ./test a1 b2 c3 thì đầu ra argv sẽ lưu "./test","a1","b2","c3"
    //và argc =4. Cái này là đối số truyền vào hàm kiểu mặc định. Tức là để chạy Ct thì thông thường sẽ có thể cần đối số thế
    //thì đối số đó lưu vào đâu-> chính là argc, argv, nếu k có thì mặc định Ct k đó đối số.Khi dùng main() thì ta dùng exit
    //(main()) để kết thúc CT cx đc, còn nếu có đối số thì phải dùng exit(main(4, argv)) ví dụ khi có 4 đối số nv

    //Khi ta chạy 1 Ct mặc định có 2 cách 1 là dùng commandPrompt chạy file exe, 2 là click đúp vào file exe để mở app-> v thì
    //thực chất vc click đúp vào là ta đã truyền vào cho nó đối số mặc định, nếu như ta muốn truyền vào đối số theo ý ta thì
    //phải dùng commandLine. Nếu ta truyền vào đối số sai thì Ct sẽ chạy sai, nếu ta truyền thừa đối số thì các đối số thừa k đc
    //dùng thôi chả cj

    //cụ thể vs Ct notepad này của ta. Đối số mặc định là(chắc cx đúng vs app khác) argc[0]:link đến file chứa exe, argv[1] mở
    //cái app này từ đâu. Bởi vì ta có thể click đúp vào notepad để mở ra 1 notepad trống or mở 1 file text và yêu cầu nó mở
    //bằng file exe kia v thì argv[1] là link của file text(vì 2 cách mở)
    //Dựa vào điều này ta dùng tính năng của notepad là mở 1 file text bất kỳ bằng app của ta bằng cách lấy argv[1] lấy đg link
    //r dùng nd đường link đó. Ta có thể tìm đối số mặc định là gì r dùng nó trong app của ta như này

    //Khi ta thao tác với argv thì nó là char* và k lưu đc unicode nên ta dùng class QTextCodec để biến nó thành tv. Tuy nhiên,
    //nó vẫn chỉ dùng đc ê chứ k dùng đc ế. Lưu ý khi dùng ta k nên dung UTF-16 mà chỉ nên dùng UTF-8 or tốt nhất là dùng codec
    //QTextCodec::codecForName("System"); để lấy cái codec cài trong máy r sẽ kbh bị lỗi(chữ tàu), hàm codecForName sẽ tìm trong
    //toàn bộ các object codec đã cài trên máy có tên best match vs "system" và lấy nó.
    //Tuy nhiên ở phiên bản mới thì nó k còn occho như v nx mà dùng hàm app.arguments().at(i) để lấy argv[i] khi chạy Ct. Điều đb
    //là nó đc dùng vs unicode sẵn luôn r. Nhưng ta gọi at(1) khi phần tử số 1 tồn tại nhé, k tồn tại mà gọi thì lỗi nên kt size.
    //Nếu ta muốn app của ta gọi từ ngoài thì tạo hàm load ngay trong main như này

    w.show();
    return a.exec();
}
