#include <QtTest/QtTest>
#include <QObject>

class TestQString: public QObject
{
    Q_OBJECT
public:
    TestQString();
private slots://các hàm test phải đặt trong slot
    void toUpper();
    void toUpper_data();//tuân thủ cấu trúc đặt tên func() và func_data() để lưu dữ liệu dạng bảng sẽ chuẩn
};
