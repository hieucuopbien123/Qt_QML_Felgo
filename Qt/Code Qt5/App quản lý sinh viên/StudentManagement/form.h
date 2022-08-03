#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMessageBox>
#include "student.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(student* tempStudent, QWidget *parent = nullptr);
    Form(student* tempStudent,QString title, QWidget *parent = nullptr);
    ~Form();

signals:
    void cancelButtonClicked(student* tempStudent);

private slots:
    void on_nameEdit_returnPressed();
    void on_okButton_clicked();
    void on_cancelButton_clicked();

public:
    void setUp();

private:
    Ui::Form *ui;
    student *tempStudent;
};

//phát hiện ra một thứ hay ho-> khi truyền biến địa chỉ vào hàm khởi tạo xong gán biến của class cho địa chỉ đó. Theo lẽ thg thì
//class bị xóa qt sẽ tự động xóa các thứ khác hộ t luôn, nhưng nó lại k xóa ở TH này vì ta truyền địa chỉ ở ngoài vào

#endif // FORM_H
