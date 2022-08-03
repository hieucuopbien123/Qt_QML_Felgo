#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->pushButton->setToolTip("Hello <font color='red'><b>World</b></font>"
                       "<ul>"
                       "<li>Item 1</li>"
                       "<li>Item 2</li>"
                       "</ul>");//ta có thể viết cái QString thành nh dòng bằng cach dùng "" ở mỗi dòng ntn
    ui->pushButton_2->setToolTip("<img src=':/new/prefix1/test.jpg'>Hello World");
    //để ảnh cùng cấp debug và trong file compile chứa main

    //phải dùng QDialog thì mới có whatsthis
    ui->pushButton->setWhatsThis("Hello <font color='red'><b>World</b></font>"
                       "<ul>"
                       "<li>Item 1</li>"
                       "<li>Item 2</li>"
                       "</ul><br />"
                       "For more info <a href='www.google.com'>Click here</a>");

    event=new eventOfWhatsThis();
    this->installEventFilter(event);
    connect(event,SIGNAL(linkClicked(const QString&)),this,SLOT(showLink(const QString&)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showLink(const QString &link)
{
    QMessageBox::information(this,"Title",link);
}
