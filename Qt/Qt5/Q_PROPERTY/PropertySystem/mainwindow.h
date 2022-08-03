#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //colorChanged mà éo bao h change thì ở đây phí
    Q_PROPERTY(QColor color MEMBER m_color NOTIFY colorChanged)
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged REVISION 1)
signals:
    void colorChanged();
    /*Q_PROPERTY là marco báo hiệu nơi đây định nghĩa 1 thuộc tính của class(thg là 1 biến nào đó).
    nó chỉ có ý nghĩa làm rõ các thuộc tính chứ về thực tế k nói lên chức năng gì trong 1 class
    kiểu biến  tên property
    READ  tên hàm get value
    WRITE  tên hàm set value
    MEMBER  tên biến//chỉ cần có MEMBER hoặc READ chứ k cần cả 2
    RESET  tên hàm đưa lại nó về mặc định
    NOTIFY  tên signal đi vs biến phát ra khi GT thay đổi
    REVISION  chỉ phiên bản của thuộc tính và singal đc sử dụng(revision number là số hiệu phiên bản)(default 0)
    khi gán cho QMetaMethod r gọi hàm revision()->nó sẽ trả về GT Q_REVISION của QObject đó
    DESIGNABLE  (default true)liệu cái property này có visible trong design GUI k
    SCRIPTABLE  (default true)liệu cái property này có thể truy cập bằng công cụ viết hay k
    STORED  (default true)liệu cái property này tùy thuộc chính nó hay phụ thuộc vào object khác. Khi ta lưu TT of cái
    object chứa property này nó có lưu k, vì nếu phụ thuộc biến khác thì k đc
    USER  (default false)liệu nó đc thiết kế cho ng dùng tự tay chỉnh sửa k.
    CONSTANT  property này có GT nào là hsố(nếu thuộc tính là hso thì k có WRITE/NOTIFY,READ luôn return 1 GT)
    FINAL  thuộc tính này k bị override bởi lớp con
    REQUIRED  chỉ rằng property này bị set bởi 1 người dùng class thì ms HĐ*/
public slots:
    Q_REVISION(1) void newMethod();//gán như v nhưng nó cx k tự thực hiện mà vẫn dùng connect. Q_PROPERTY giúp code
    //rõ ràng thôi và đc dùng thêm hàm setProperty/property/dynamicPropertyNames và lấy đc vài GT thông qua QMeta mà thôi
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)

    Priority priority() const;
    void setPriority(const Priority &priority);

signals:
    void priorityChanged(Priority);

private:
    Ui::MainWindow *ui;
    Priority m_priority;
    QColor  m_color;
};
#endif // MAINWINDOW_H
