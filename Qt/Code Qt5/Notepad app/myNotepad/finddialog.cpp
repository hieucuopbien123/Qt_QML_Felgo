#include "finddialog.h"
#include "ui_finddialog.h"

Finddialog::Finddialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finddialog)
{
    ui->setupUi(this);
}

Finddialog::~Finddialog()
{
    delete ui;
}


void Finddialog::on_pushButton_clicked()
{
    emit find(ui->lineEdit->text());
}

void Finddialog::on_pushButton_2_clicked()
{
    this->close();
}
