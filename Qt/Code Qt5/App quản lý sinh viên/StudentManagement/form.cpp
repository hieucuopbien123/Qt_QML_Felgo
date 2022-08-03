#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(student* tempStudent, QWidget *parent) :
    QWidget(parent),//mấy cái này yêu cầu phải khai báo trc, các biến càng phức tạp càng khai báo trc
    ui(new Ui::Form),
    tempStudent(tempStudent)
{
    ui->setupUi(this);

    setUp();
}

Form::Form(student* tempStudent,QString title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    tempStudent(tempStudent)
{
    ui->setupUi(this);
    ui->titleLabel->setText("<html><head/><body><p align='center'><span style=' font-size:12pt;"
                            " font-weight:600; color:#7e7e7e;'>" + title + "</span></p></body></html>");
    //chú ý dấu "" thay thành '' ở trong html
    setUp();
}

void Form::setUp()
{
    ui->nameEdit->setText(this->tempStudent->name);
    ui->ageEdit->setValue(this->tempStudent->age);
    if(this->tempStudent->sex.compare("male",Qt::CaseInsensitive) == 0)
    {
        ui->maleEdit->setChecked(true);
    }
    else if(this->tempStudent->sex.compare("female",Qt::CaseInsensitive) == 0)
        ui->femaleEdit->setChecked(true);
    if(this->tempStudent->type.compare("good",Qt::CaseInsensitive) == 0)
    {
        ui->goodEdit->setChecked(true);
    }
    else if(this->tempStudent->type.compare("medium",Qt::CaseInsensitive) == 0){
        ui->mediumEdit->setChecked(true);
    }
    else if(this->tempStudent->type.compare("bad",Qt::CaseInsensitive) == 0){
        ui->badEdit->setChecked(true);
    }
    if(!this->tempStudent->description.isEmpty() && this->tempStudent->description.compare("You are ..."))
    {
        ui->descriptionEdit->setText(this->tempStudent->description);
    }
    else
    {
        ui->descriptionGroup->setChecked(false);
    }
    //cái textEdit khi dùng set cho nó font chữ các thứ kèm chữ sẵn trong design sẵn nó sẽ lưu lại,xóa hết chữ lại về mặc định
}

Form::~Form()
{
    delete ui;
}

void Form::on_nameEdit_returnPressed()
{
    on_okButton_clicked();
}

void Form::on_okButton_clicked()
{
    tempStudent->name = ui->nameEdit->text();
    tempStudent->age = ui->ageEdit->value();
    if(ui->buttonGroup->checkedButton() != nullptr)
        tempStudent->sex = ui->buttonGroup->checkedButton()->text();//trap gán thì phải check xem có GT k ms gán đc chứ
    if(ui->buttonGroup_2->checkedButton() != nullptr)
        tempStudent->type = ui->buttonGroup_2->checkedButton()->text();
    if(ui->descriptionGroup->isChecked())
        tempStudent->description = ui->descriptionEdit->toPlainText();//chú ý nó éo có text() mà là toPlainText()

    if(!tempStudent->name.isEmpty())
    {
        emit tempStudent->dataChanged(tempStudent);

        this->close();
        this->deleteLater();
    }
    else
    {
        QMessageBox::warning(this,"Lack of information!","Please input a name");
    }
}

void Form::on_cancelButton_clicked()
{
    this->close();
    this->deleteLater();

    emit cancelButtonClicked(tempStudent);
}
