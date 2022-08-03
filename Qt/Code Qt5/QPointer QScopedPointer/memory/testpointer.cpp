#include "testpointer.h"
#include <QDebug>

TestPointer::TestPointer(QObject *parent) : QObject(parent)
{
    QPointer<TestObjectPointer> object = new TestObjectPointer;
    //QPointer như 1 con trỏ bth của C++ nhưng sự khác biệt là khi xóa biến thì con trỏ tự động set về null
    //Nó có vẻ vô dụng và chỉ dung với QObject

    connect(object,SIGNAL(printHello()),this,SLOT(printHello()));
    connect(this,SIGNAL(test()),object,SIGNAL(printHello()));
    //Tức là dùng QPointer như kiểu xóa đi thì gán NULL tránh con trỏ lơ lửng thôi.
    //Nếu k xóa đi như này sẽ bị memory leak. Vì đúng là qt có cơ chế tự xóa các biến thành viên khi class bị xóa
    //nhưng biến object bên trên thì kp thành viên, trừ khi dùng this đằng sau. Nó như 1 biến con trỏ truyền từ ngoài
    //vào v, đây là TH cần tránh dùng vì ra khỏi hàm k còn biến trò đến để dùng đc nx+phải chủ động xóa nhé

    connect(this,SIGNAL(destroyed()),object,SLOT(deleteLater()));
}

void TestPointer::printHello()
{
    qDebug() << "Hello";
}
