#include "testobject.h"

MyWidget::MyWidget()
{
    myButton = new QPushButton(this);
    connect(myButton, SIGNAL(clicked()),
            this, SIGNAL(buttonClicked()));//connect SIGNAL cho phat 1 SIGNAL khác cx đc
//    startTimer(50);     // 50-millisecond timer
//    startTimer(1000);   // 1-second timer
//    startTimer(60000);  // 1-minute timer

    using namespace std::chrono;
//    startTimer(milliseconds(50));
//    startTimer(seconds(1));
//    startTimer(minutes(1));

    // since C++14 we can use std::chrono::duration literals, e.g.://đổi file pro CONFIG+=c++14
    startTimer(100ms);
//    startTimer(5s);
//    startTimer(2min);
//    startTimer(1h);

    //hàm startTimer sẽ bắt đầu đếm ngược bao nhiêu miligiay.Thực chất ta ko thể dùng đc nó chỉ như thế này. Sau mỗi ktg cái timer chạy
    //là đối số ta truyền vào nó sẽ lặp lại liên tục và gọi hàm protected là timerEvent của QObject(tự động)
}
void MyWidget::timerEvent(QTimerEvent *e) {

  Q_UNUSED(e);//cái này chỉ là làm mất warning

  QTime qtime = QTime::currentTime();
  QString stime = qtime.toString();
  QLabel *label=new QLabel;
  label->setText(stime);
  //ở đây giả sử ta cần hiển thị 1 cái label chứa time hiện tại lên màn hình với cái đồng hồ cập nhập sau mỗi 100ms.
  //thì ta dùng hàm này kết hợp startTimer bên trên
  //hàm timerEvent là protected mặc đinh truyền vào QTimerEvent.Ta có thể dùng timerID của QTimerEvent nhưng ở đây ta k dùng
}

void MyWidget::testIsSignalConnected()
{
    static const QMetaMethod destroyedWidget = QMetaMethod::fromSignal(&QObject::destroyed);//destroy k cản đc bởi block
    //cách ss 2 signal
//mỗi biến QMetaMethod sẽ lưu thông tin của 1 signal đc gán cho nó-biến giúp ta thao tác với signal vd KT signal(thực chất là cả QOBject)
    if (isSignalConnected(destroyedWidget)) {//hàm KT xem signal có connect vs receiver k
        //dosth, thậm chí emit cái signal khác trong đây cx ok. Khi gọi hàm nó sẽ kiểm tra xem biến QMetaMethod(là signal) có liên kết với
        //1 cái receiver nào k(ta có thể truyền vào biến QMetaMethod or bky signal nào để KT biến đó cx ok)
        //signal ta dùng trong CT là 1 kiểu biến QMetaMethod
    }
    if (receivers(SIGNAL(valueChanged(QByteArray))) > 0) {
        //hàm receivers truyền vào signal để KT số lượng receivers kết nối đến nó, pb vs hàm trên chỉ KT có kết nối hay k
    }
    //cả 2 hàm kiểm tra signal có đc connect k vào bnh connect đều là protected->buộc kế thừa và dùng bên trong class thôi
}
//trong Qt có các hàm đặc biệt có sự liên kết với nhau, và nhiều hàm nó yêu cầu nên có bằng cách ta định nghĩa lại vì bên
//bên trong nó éo có gì cả. Vd các hàm về event. installEventFilter sẽ gán cho QObject cái event, mà cái event đc truyền
//vào ở 1 hàm khác là evenFilter(2 hàm liên kết với nhau).Mà hàm eventFilter của QObject nó chả làm gì cả mà yêu cầu ta
//tự định nghĩa lại override để nhét cái eventFilter cho nó=>nó chỉ đưa cấu trúc sẵn, ta phải tự làm->sai
