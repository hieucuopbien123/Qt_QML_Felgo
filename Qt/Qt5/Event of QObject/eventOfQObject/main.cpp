#include "widget.h"
#include <QApplication>

class key:public QWidget
{
public:
    key(){;};
protected:
    bool eventFilter(QObject *obj, QEvent *event)
    {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            qDebug("Ate key press %d", keyEvent->key());
            return true;
        } else {
            // standard event processing
            return QObject::eventFilter(obj, event);
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    key *k=new key;
    w.installEventFilter(k);
//    w.removeEventFilter(k);
    w.show();

    //Thực hành mọi hàm event của QObject

    //hàm event(QEvent*) của QObject giúp mọi Object thực hiện các event bất kỳ và ta cần định nghĩa hàm đó với đối số y
    //hệt như v với override-> nó sẽ tự động thực hiện trong suốt quá trình cái biến tồn tại, cứ có event là bắt và thực
    //hiện bên trong. Chính vì v bên trong ta thg dùng đk if gặp cái gì thì làm gì-> nó như kiểu signal slot nhưng ở đây
    //là sự kiện nên có nh thứ khác.

    //hàm installEventFilter(QObject*) sẽ cài cho cái QObject hiện tại một cái QObject khác. Trong Qt do clean code nên
    //ta có thể định nghĩa 1 class riêng QObject chỉ làm 1 nv duy nhất là filter event. Thì cái eventFilter này là 1 biến
    //QObject(ở trên là class key). Khi dùng installQEventFilter thì hàm event của QObject đó coi như bỏ mà thực hiện như
    //trong eventFilter => x removeEventFilter
    //đúng ra là k bỏ-> khi eventFilter và event đc set cho 1 object thì nó sẽ chạy liên cmn tục luôn k ngừng chứ kp chỉ
    //có sự kiện ms chạy mà là chạy liên tục nếu đúng dự kiện ms thực hiện trong if. Tuy nhiên 1 sự kiện chỉ đc bắt 1 lần
    //nên nếu eventFilter và event cùng bắt 1 sự kiện thì eventFilter sẽ ưu tiên bắt trc nên event k bắt nx ở TH này thôi

    //hàm eventFilter của QObject sẽ giúp biến cái QObject thành 1 bộ lọc sự kiện cho các QObject khác. Giả sử có nh
    //QObject cùng thực hiện sk như nhau thì chỉ cần installEventFilter là xong. Hàm eventFilter(QObject*,QEvent*) nhận
    //2 đối số vì có thể có nhiều QObject install nó, nên lọc luôn cả QObject bên trong tùy đk if do ta viết chỉ những
    //QObject nào ms đc(VD chuẩn lọc QObject viết ở learnLibrary oldGeneration)

    //hàm children của QObject sẽ lấy ra 1 list các QObject là con của nó. Tức là các thứ cấp 1 chứa trong nó.
    //chẳng hạn QWidget chứa 1 "button", 1 "label" thì children sẽ cho ra list QObject* gồm button và label. Trường hợp
    //button và label lại cùng bị nhét trong 1 Layout thì dùng ui sẽ lấy ra mỗi layout đó, dùng code thì lấy tất cả TP.

    //childEvent() và customEvent() đều là giống hàm event() kiểm tra event và thực thi, nhưng mà childEvent sẽ nhận vào
    //kiểu QChildEvent* cũng là 1 kiểu event kế thừa từ QEvent. Đó là hàm tự động, 1 QObject con nào đó của QObject HT
    //bị xóa hoặc thêm vào thì hàm này sẽ tự chạy->nhét event của con vào cha.Còn customEvent() nhận vào kiểu QEvent*
    //nhưng thực chất là nhận vào QEvent do chính ta tạo ra, ta tự tạo 1 event có type riêng và nó sẽ bắt.

    //startTimer(tg)sẽ bắt đầu chạy 1 cái timer, và phát ra 1 sự kiện QTimerEvent sau mỗi 1 ktg là đối số truyền vào,hàm
    //timerEvent sẽ bắt sự kiện đó và chạy cái bên trong. Ta có thể chạy nhiều timer thoải mái vì mỗi cái timerEvent có 1 cái
    //timerId trong biến QTimerEvent.=> để dừng dùng killTimer(id).

    return a.exec();
}
