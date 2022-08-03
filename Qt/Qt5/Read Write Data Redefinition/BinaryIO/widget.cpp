#include "widget.h"
#include "ui_widget.h"
#include "Overload.h"//khi khai báo thêm các operator gì cho 1 class có sẵn thì phải include ở trong file cpp TT dùng,kp file h

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    save();
    load();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::save()
{
    MyClass person1;
    person1.name = "Hieu";
    person1.age = 18;

    MyClass person2;
    person2.name = "Alone";
    person2.age = 20;

    QFile file("./Test.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannot open file for save!";
        return;
    }
    QDataStream save(&file);
    save.setVersion(QDataStream::Qt_5_9);//đảm bảo hoạt động tốt với phiên bản mới nhất
    save << person1;
    save << person2;

    file.flush();
    file.close();
}

void Widget::load()
{
    MyClass person1;
    MyClass person2;

    QFile file("./Test.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open file for save!";
        return;
    }
    QDataStream save(&file);
    save.setVersion(QDataStream::Qt_5_9);//đảm bảo hoạt động tốt với phiên bản mới nhất
    save >> person1;
    save >> person2;

    file.close();

    qDebug() << "Person 1: " << person1.name << " " << person1.age;
    qDebug() << "Person 2: " << person2.name << " " << person2.age;
}

