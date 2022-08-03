#include <QCoreApplication>
#include "testpointer.h"
#include <QScopedPointer>
#include <QDebug>

int* TestScopedPointer()
{
    QScopedPointer<int> pointer(new int(23));
    qDebug() << pointer.data();//or dùng pointer.get();

    int* b = pointer.take();
    //take sẽ xóa ScopedPointer ngay lập tức, và trả ra giá trị con trỏ thành 1 biến độc lập.
    //còn get sẽ trả ra int nhưng k xóa ScopedPointer thành null(cả 2 dùng chung địa chỉ đó)

    return b;
    //dùng get thì quyền sở hữu vẫn là của biến QScopedPointer, dùng take() thì biến pointer = null và đưa lại quyền sở hữu cho
    //người dùng là biến int* do đó cần 1 cái lưu nó lại và dùng or k dùng thì phải chủ động xóa

    //1 điều đặc biệt là ra khỏi hàm ScopedPointer sẽ tự động bị xóa, nếu nó đang đi với 1 con trỏ nào đó ví dụ int thì
    //cái vùng nhớ int* đó cx bị xóa theo. Dẫn đến 1 lỗi sai là return scopedPointer.get()=> hàm này sai nặng, vì return tức
    //ra khỏi hàm thì scopedpointer sẽ bị xóa, khi đó con trỏ k thể dùng đc ở ngoài nhưng ở đây ta lại return để dùng nó ở
    //ngoài sẽ segmentfault core dump. Nhưng nếu ta dùng take như ở trên thì quá ok, nó sẽ delete scopedpointer và cái int* trở
    //thành độc lập nên dùng đc ở ngoái. Quy tắc ra khỏi hàm là xóa là bắt buộc vì cơ chế dùng stack
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestPointer test;
    emit test.test();

    int* pointer = TestScopedPointer();
    qDebug() << pointer;
    //QScopedPointer sẽ tự động xóa vs cơ chế: gán quyên sở hữu vùng nhớ trên heap cho 1 stack, như v khi ra khỏi phạm vi lập
    //tức bị xóa.Ví dụ khi biến con trỏ của ta có nhiều TH exit point.Mỗi TH ta lại phải delete nó ms chết->dùng QScopedPointer
    delete(pointer); //dùng take nên trở về quyền sở hữu of ta vì scopedPointer sẽ mất vai trò nên trở về pointer bth k tự xóa

    return a.exec();
}
