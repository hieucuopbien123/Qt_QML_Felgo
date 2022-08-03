#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QStringList strList;
    strList << "Hieu" << "Hung" << "Hong" << "Trang" << "Hien";
    strCompleter = new QCompleter(strList,this);//nếu dùng QStringListModel thì có thể đổi liên tục đc vì dùng con trỏ
    strCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(strCompleter);

    modelCompleter = new QCompleter(this);
    modelCompleter->setModel(new QDirModel(modelCompleter));//modelCompleter truyền vào với vai trò như 1 QObject
    //nên dùng như này sẽ tối ưu vì completer mất thì QDirModel cx mất. Cũng dùng vs các model khác
    ui->lineEdit_2->setCompleter(modelCompleter);
    //tạo QCompleter->set nội dung,mode case sensitive->setCompleter cái đó
}

Dialog::~Dialog()
{
    delete ui;
}

