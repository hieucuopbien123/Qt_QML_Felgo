#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QLabel *label=new QLabel("Name: ");
    QLineEdit *lineEdit=new QLineEdit;
    QPushButton *button=new QPushButton{"Test"};
    QGridLayout *gLayout=new QGridLayout;
    gLayout->addWidget(label,0,0);
    gLayout->addWidget(lineEdit,0,1);
    gLayout->addWidget(button,1,1,1,2);

    QPushButton *button1=new QPushButton("test 1");
    QPushButton *button2=new QPushButton("test 2");
    QSplitter *splitter=new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(button1);
    splitter->addWidget(button2);
    gLayout->addWidget(splitter,2,1,1,3);
    //dùng splitter cả code cả design. Vs code, nhét vào trong layout cx ok

    this->setLayout(gLayout);
    //hiện tất cả đè lên nhau

    //chỉnh button ra giữa bên trên ta phải chỉnh sizepolicy của nó về fixed rồi set 2 cái spacer 2 bên, 1 spacer ở dưới
    //2 button đặt trong 1 splitter rồi thì nó đóng vai trò là 1 layout rồi, nhưng ta lồng nó vào layout nx cx chả sao
    //nói chung mấy cái size vị trí này thì cứ ui form mà quất r copy code ra
}

Widget::~Widget()
{
    delete ui;
}

