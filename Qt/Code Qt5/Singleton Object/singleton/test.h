#ifndef TEST_H
#define TEST_H

#include <QObject>
#include "Singleton.h"

class test : public QObject
{
    Q_OBJECT
public:
    explicit test(QObject *parent = 0);

    static void doSomething();

signals:
    void testSignal();

public slots:

};
//tức là ta dùng Singleton<test>::Instance() thì dài nên đặt Tester::Instance(), k có cx đc

//Global unique variable is Tester::Instance()
typedef Singleton<test> Tester;//đặt tên khác cho biến của class-> nó là biến global dùng ở bất cứ đâu và là duy nhất
//truy xuất thông qua instance=>thật ra cũng chỉ là 1 biến global con trỏ của class mà thôi.
//để dùng: include cái class singleton vào->khởi tạo ra 1 biến singleton<tên class> ở ngay cuối class như này(k cần)-> truy
//xuất mọi lúc với ::instance là 1 con trỏ global của class k phải sợ k dùng đc hàm instance trong static nx
//Ví dụ: ta muốn emit 1 signal của 1 class mà k có biến thì dùng singleton patern

//Lưu ý rằng ta k hề tạo bất cứ 1 biến singleton nào. Nó k hề có instance, ta đơn giản là dùng hàm static ::Instance của nó
//mà thôi. Điều này đảm bảo 1 class chỉ có 1 instance duy nhất(k có cách nào tạo ra 2 trừ khi include 2 class singleton).
//Gọi Singleton<test>::Instance() 1 lần là có đc biến static* của class. Sau đó truy xuất hàm của class bằng -> thôi
//Tức hàm static của singleton là Instance()lại tạo ra 1 biến T* duy nhất và sử dụng nó.Nếu T đổi sẽ có instance class khác

//dùng như này chú ý biến nằm trong mainthread và chỉ giải phóng khi Ct kết thúc hay ~Singleton<T> thì các biến T mới tự bị xóa
//Đó là bản chất của global instance 1 số class

#endif // TEST_H
