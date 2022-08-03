#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPushButton *button1=new QPushButton("Button 1");
    button1->setObjectName("H");
    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->setObjectName("I");
    hLayout->addWidget(button1);
    this->setLayout(hLayout);

    QList<QObject*> ObjectList=this->children();
    for(int i=0;i<ObjectList.size();i++)
    {
        qDebug() << ObjectList.at(i)->objectName();
    }

    using namespace std::chrono;
    startTimer(100ms);//giá trị int trả ra cx là timerId của event
}

void Widget::timerEvent(QTimerEvent *event)
{
    ui->label->setText(QTime().currentTime().toString());
//    killTimer(event->timerId());
}

Widget::~Widget()
{
    delete ui;
}
