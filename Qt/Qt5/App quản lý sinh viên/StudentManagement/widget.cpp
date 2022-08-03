#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    num = 0;

    ui->studentManagementEdit->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_addingButton_clicked()
{
    student* newStudent = new student();
    studentList << newStudent;
    QTreeWidgetItem* newItem = new QTreeWidgetItem();
    newItem->setText(0,newStudent->name);
    newItem->setText(1,newStudent->type);
    ui->studentManagementEdit->addTopLevelItem(newItem);

    Form *dialog = new Form(newStudent);
    dialog->show();
    /*chú ý trap hàm khai báo. Khi ta khai báo class vs đối số this, Vd Form *dialog(newStudent, this); thì nó mang 2 ý nghĩa:
    //nếu this bị xóa thì dialog cx bị xóa, dialog là con của this=> Khi khai báo this, thì this đóng VT là QWidget vì Form kế
    //thừa từ QWidget nên nó lấy this để khai báo QWidget nên nếu this bị xóa thì QWidget lớp mẹ cx bị xóa nên Form bị xóa; Khi
    //khai báo this thì nó đóng vai trò là con và nằm bên trong, tức nó là 1 thành phần của this. Cái hay là vc ta cứ tưởng vc
    //khai báo biến thành viên thì ms là con của class và nằm bên trong class, nhưng vs cách này ta có thể biến bất cứ 1 biến
    //con trỏ nào kế cả chỉ khai báo tức thời trong hàm thành con của class đều thành biến thành viên của class đc.
    //Vấn đề qtr hơn là: khi ta xóa this thì dialog bị xóa, nhưng xóa dialog thì this lại k bị xóa mặc dù ta truyền con trỏ.
    //Trong Qt dù khi xóa class thì các biến thành viên và thuộc tính lớp kế thừa đều tự động xóa nhưng nó đủ thông minh để
    //xác định biến con trỏ truyền vào hàm khởi tạo k bị ảnh hưởng, do đó ta truyền newStudent là con trỏ vào và chỉ cần k gọi
    //hàm xóa nó trong dialog thì nó sẽ k bị xóa dù dialog bị xóa=> mở ra nh cách thao tác với các cửa sổ và lưu dữ liệu*/

    /*trap nặng: đừng bắt chước video mà dùng lamba function, ở đây là lamba vs this nên nó chỉ thao tác đc vs các thứ trong
    //this chứ k đc dùng các biến k thuộc phạm vi của đối số 3. Ở đây ta vẫn dùng newStudent đc vì nó là 1 tp của class do
    //nó ở trong vector và ta đang truy cập vào địa chỉ thì cx như nó là tp của class còn newItem thì vỡ mồm nhé, trừ khi có
    //list<QListWidgetItem*>
    //    connect(dialog,&Form::cancelButtonClicked,this,[&]()
    //    {
    //        studentList.removeOne(newStudent);
    //        //        ui->studentManagementEdit->takeItem(ui->studentManagementEdit->row(newItem));
    //        //        newItem->~QListWidgetItem();
    //        newStudent->~student();
    //        qDebug() << student2->age;
    //    })*/
    connect(newStudent,&student::dataChanged,this,[&](student* changedStudent)
    {
        int index = studentList.indexOf(changedStudent);
        QTreeWidgetItem* changedItem = ui->studentManagementEdit->topLevelItem(index);

        changedItem->setText(0,changedStudent->name);
        changedItem->setText(1,changedStudent->type);

        ui->studentManagementEdit->setCurrentItem(changedItem);
    });
    connect(dialog,&Form::cancelButtonClicked,this,[&](student* erasedStudent)
    {
        int index = studentList.indexOf(erasedStudent);

        studentList.removeOne(erasedStudent);
        erasedStudent->~student();

        QTreeWidgetItem* erasedItem = ui->studentManagementEdit->takeTopLevelItem(index);//hàm take là xóa
        erasedItem->~QTreeWidgetItem();
    });
}

void Widget::on_addingMultButton_clicked()
{
    num = QInputDialog::getInt(this,"Add multi students","How many students you want to add",1,1,1000);

    student* newStudent=new student();
    studentList << newStudent;
    QTreeWidgetItem* newItem = new QTreeWidgetItem();
    newItem->setText(0,newStudent->name);
    newItem->setText(1,newStudent->type);
    ui->studentManagementEdit->addTopLevelItem(newItem);

    Form *dialog=new Form(newStudent);
    dialog->show();

    connect(newStudent,&student::dataChanged,this,[&](student* changedStudent)
    {
        int index = studentList.indexOf(changedStudent);
        QTreeWidgetItem* changedItem = ui->studentManagementEdit->topLevelItem(index);
        changedItem->setText(0,changedStudent->name);
        changedItem->setText(1,changedStudent->type);
        ui->studentManagementEdit->setCurrentItem(changedItem);

        for(int i = 0;i < num - 1;i++)
        {
            student* newDuplicateStudent = new student();
            newDuplicateStudent->name = changedStudent->name;
            newDuplicateStudent->age = changedStudent->age;
            newDuplicateStudent->sex = changedStudent->sex;
            newDuplicateStudent->type = changedStudent->type;
            newDuplicateStudent->description = changedStudent->description;

            studentList << newDuplicateStudent;
            QTreeWidgetItem* newDuplicateItem = new QTreeWidgetItem();
            newDuplicateItem->setText(0,newDuplicateStudent->name);
            newDuplicateItem->setText(1,newDuplicateStudent->type);
            ui->studentManagementEdit->addTopLevelItem(newDuplicateItem);
        }
    });
    connect(dialog,&Form::cancelButtonClicked,this,[&](student* erasedStudent)
    {
        int index = studentList.indexOf(erasedStudent);

        studentList.removeOne(erasedStudent);
        erasedStudent->~student();

        QTreeWidgetItem* erasedItem = ui->studentManagementEdit->takeTopLevelItem(index);
        erasedItem->~QTreeWidgetItem();
    });
}

void Widget::on_studentManagementEdit_itemActivated(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    int index = ui->studentManagementEdit->indexOfTopLevelItem(item);
    student* adjustStudent = studentList.at(index);

    Form *dialog = new Form(adjustStudent,"Edit student: " + adjustStudent->name);
    dialog->show();

    connect(adjustStudent,&student::dataChanged,this,[&](student* changedStudent)
    {
        int index = studentList.indexOf(changedStudent);

        QTreeWidgetItem* changedItem = ui->studentManagementEdit->topLevelItem(index);

        changedItem->setText(0,changedStudent->name);
        changedItem->setText(1,changedStudent->type);

        ui->studentManagementEdit->setCurrentItem(changedItem);
    });
    //trap đã bắt signal này ở bên trên r mà biên k bị xóa thì vẫn có, làm v sẽ thực hiện 2 lần mất
}

void Widget::on_removingButton_clicked()
{
    if(studentList.size() <= 0)
    {
        return;
    }

    //    đây là xóa 1 item
    QTreeWidgetItem* erasedItem = ui->studentManagementEdit->currentItem();//nó k trả null tức là k chọn j thì current
    //item là cái trên cùng
    int index = ui->studentManagementEdit->indexOfTopLevelItem(erasedItem);
    student* erasedStudent = studentList.at(index);

    studentList.remove(index);
    erasedStudent->~student();

    ui->studentManagementEdit->takeTopLevelItem(index);
    erasedItem->~QTreeWidgetItem();

    /*    QItemSelectionModel* model = ui->studentManagementEdit->selectionModel();
    //    qDebug() << "1";
    //    QModelIndexList indexList = model->selectedIndexes();
    //    qDebug() << "2";
    //    foreach(QModelIndex index, indexList)
    //    {
    //        qDebug() << indexList.size() << " " << index.row();
    //        student* student=studentList.at(index.row());
    //        qDebug() << index.row();
    //        QTreeWidgetItem* erasedItem = ui->studentManagementEdit->topLevelItem(index.row());
    //        qDebug() << index.row();

    //        //xóa student khỏi list
    //        studentList.remove(index.row());
    //        qDebug() << index.row();
    //        //xóa student
    //        student->~student();
    //        qDebug() << index.row();
    //        //xóa item khỏi listWidget
    //        ui->studentManagementEdit->takeTopLevelItem(index.row());
    //        qDebug() << index.row();
    //        //xóa item
    //        erasedItem->~QTreeWidgetItem();
    //    }
    //ngu ngốc: mô hình item base là mô hình quản lý từng item một-> mặc dù nó kế thừa nhưng k đc dùng cj lq đến model
    //nếu k sẽ xh các lỗi k mong muốn-> muốn thao tác với nhiều phần tử toàn diện hơn thì dùng MVC, nếu số lượng ít,
    //thao tác ít phần tử thì dùng item base. Ở tren ta cố dùng và toang-> k thể chọn nhiều phần tử với item base*/
}

//hướng phát triển:ấn remove thì hiện QMessageBox có chắc muốn xóa; dùng MVC để chọn xóa nhiều; sau khi add multi thì sẽ chọn
//tất cả các phần tử vừa tạo luôn; lưu dữ liệu vào file khi đóng và khi mở thì đọc tiếp từ file ra và k bị mất=> mở rộng thành
//QMainWindow có nút save và nút open sẽ hiển thị tất cả các file trong thư mục lưu thành database và sẽ đọc từ file ra thành
//list student tùy file nào ng dùng chọn
