#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "watcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w=new MainWindow();
    Watcher* watcher = new Watcher();
    QObject *object = w;

    object->setProperty("priority", "Low");//tự có
    /*setProperty gán 1 thuộc tính property của QObject cho 1 GT nào đó, 1 là tên property,2 là GT
    nếu property của object đã đc khai báo bằng Q_PROPERTY thì truy cập đc nó với property và hàm setProperty trả true
    nếu property của QObject chưa khai báo bằng Q_PROPERTY thì chỉ truy cập đc bằng dynamicPropertyNames->set trả false
    tức là ta có thể set property là cj có giá trị gì cho 1 biến dynamic bất cứ lúc nào cx đc*/

    //Nếu k có Q_PROPERTY thì ta dùng getter,setter bth để dùng sử dụng 1 thuộc tính nào đó của class. Có nó thì ta
    //dùng đc property và setProperty nx nhưng như v thì vô dụng, điều quan trọng là nó dùng databinding với qml
    QObject::connect(w, &MainWindow::priorityChanged, watcher, &Watcher::priorityChanged);
    //Phải có cái này thì mới dùng được các biến của class c++ trong qml, nó sẽ tự kết nối signal slot như này cho qml

    //Dùng Property trong C++
    w->setProperty("priority", MainWindow::Priority::VeryHigh);//Qt < 6
    w->setProperty("priority", QVariant(MainWindow::VeryLow));//Qt6 bắt buộc dùng như này
    //Dùng C++ thủ công
    w->setPriority(MainWindow::Low);
    //Dùng QML tương tác với class C++ đó=>nhiều ngôn ngữ khác cx có thể tương tác với C++ class = Q_PROPERTY, QML là 1 VD
    //w.message = MainWindow::High;
    w->show();

    return a.exec();
}
