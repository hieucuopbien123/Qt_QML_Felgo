#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QApplication>
#include <QtWidgets>

class MyWidget : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("Author", "Hieu")
    Q_CLASSINFO("URL", "http://...")
    //nó cung cáp info về class truyền vào name và value
private:
    Q_DISABLE_COPY(MyWidget)
    //Marco này k cho phép hàm dùng hàm khởi tạo copy. Ví dụ ta khai báo MyWidget a; rồi ta đinh nghĩa 1 hàm khởi tạo copy và dùng
    //MyWidget b(a); or b=a do nhầm lẫn thì nó sẽ báo lỗi.Tuy nhiên có 1 số TH k như v nó sẽ k báo lỗi VD QWidget có cái marco này mà ta
    //dùng QWidget w = QWidget(); thì cx là 1 hàm khởi tạo copy nhưng nó khác là khởi tạo bth 1 QWidget() trống r sau đó ms gán cho w
    //ở Th này nó sẽ k báo lỗi nhưng CT crash khi dùng=> Tốt nhất là cần KT kĩ nếu khỏi tạo kiểu copy xem có marco này k
public:
    MyWidget();
    bool event(QEvent* ev) override
    {
        if (ev->type() == QEvent::PolishRequest) {
            // overwrite handling of PolishRequest if any
            return true;
        } else  if (ev->type() == QEvent::Show) {
            // complement handling of Show if any
            QWidget::event(ev);
            return true;
        }
        // Make sure the rest of events are handled
        return QWidget::event(ev);
        //cả hai QWidget và QObject đều có event(QEvent*) là hàm trả về true nếu cái sự kiện e đc nhận dạng và xử lí
        //ta dùng hàm này ở cuối để chắc rằng nó đc xử lí nếu k rơi vào TH ta yêu cầu, nếu k return false;
        //hàm này là hàm public nhưng nó k làm j cả, ta phải tự định nghĩa làm gì với cái event đó(làm gì thì sang QEvent sẽ học)
    }
    bool eventFilter(QObject *obj, QEvent *event) override//use for internal purposes
    {//trả về true nếu filter dc, false là k filter
        if (obj == myButton) {//kiểm chứng đc QObject có là QObject của biến nào k như này để lọc ĐK
            if (event->type() == QEvent::KeyPress) {
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                qDebug() << "Ate key press" << keyEvent->key();
                return true;
            } else {
                return false;
            }
        } else {
            return QWidget::eventFilter(obj, event);
            //ta đều có thói quen pass cho parent xử lí(dù nó k làm gì cả) để k bh bị thừa event k làm gì cả
            //class này gọi hàm của QObject, nếu k đc thì gọi hàm cha là QWidget, nhưng QWidget cx gọi vào hàm đó của QObject mà thôi(chả làm j hết)
        }
        //hàm này TT nhưng nó Filter cái event thông qua QObject, tức kiểm tra thêm biến QObject
    }
    void testIsSignalConnected();
    Q_INVOKABLE void timerEvent(QTimerEvent *e) override;
    //Marco Q_INVOKABLE làm cho hàm có thể đc invoke thông qua meta-object system(cái hệ thông signal slot j đó)

    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)//dùng marco này khi dùng enum

    enum SelectionFlag {
            NoUpdate       = 0x0000,
            Clear          = 0x0001,
            Select         = 0x0002,
            Deselect       = 0x0004,
            Toggle         = 0x0008,
            Current        = 0x0010,
            Rows           = 0x0020,
            Columns        = 0x0040,
            SelectCurrent  = Select | Current,
            ToggleCurrent  = Toggle | Current,
            ClearAndSelect = Clear | Select
        };
        Q_DECLARE_FLAGS(SelectionFlags, SelectionFlag)//của QFlag chuyển thành flag từ enum nào->dùng flag bên dưới
        Q_FLAG(SelectionFlags)//dùng cái nào cx đc,nó báo rằng gt của eunm có thể đc dùng làm GT bit cờ

Q_SIGNAL void buttonClicked();

private:
QPushButton *myButton;
//Q_REVISION,Q_PROPERTY,Q_NAMESPACE_EXPORT,Q_INTERFACES,Q_SINGAL,Q_SLIGNALS,Q_SLOT,Q_SLOTS,Q_FLAG_N,
//Q_SET_OBJECT_NAME,Q_EMIT,Q_DISABLE_COPY_MOVE,Q_DISABLE_MOVE,Q_EMIT,Q_ENUM_NS
//(Q_NAMESPACE_EXPORT giống Q_NAMESPACE nhưng có ích khi cần exported từ 1 dynamic library),(Q_SIGNAL giống Q_SIGNALS và
//từ khóa signals->giúp mark 1 function là signal,có ích khi phần mềm bên thứ 3 k hiểu Q_SIGNALS và signals thì dùng)
};

#endif // TESTOBJECT_H
