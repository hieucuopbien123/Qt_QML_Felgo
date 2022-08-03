#include <QCoreApplication>
#include <QVariant>
#include <QDebug>
#include "myclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVariant v = 123.02;
    //Biến này cần có để lưu thông tin các kiểu biến khác. Họ muốn 1 loại biến gán cj cx đc và lấy ra lúc nào cần
    //ví dụ 1 Ct nhận int nhưng ng dùng thích nhập double or string cơ thì dùng qvariant tránh crash ct
    qDebug() << v.toInt();
    if(v.canConvert<QString>())
    {
        qDebug() << v.toString();//dùng value<QString>() cx đc nhưng nó là tổng quát và thg dùng cho kiểu class
    }

    myclass mClass;
    mClass.number = 222;
    QVariant z = QVariant::fromValue(mClass);//QDataStream cx lưu đc class nhưng theo chuỗi basic data,cái này lưu 1 biến
    myclass zClass = z.value<myclass>();//hàm này nó có kiểm tra xem có canConvert k ms thực hiện
    qDebug() << zClass.number;



    return a.exec();
}
