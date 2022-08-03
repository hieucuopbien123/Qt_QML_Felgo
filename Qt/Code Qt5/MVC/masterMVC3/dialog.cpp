#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //khởi tạo
    standardModel=new QStandardItemModel(4,2,this);
    for(int row=0;row<standardModel->rowCount();row++)
    {
        for(int col=0;col<standardModel->columnCount();col++)
        {
            QModelIndex index=standardModel->index(row,col);
            //hàm index của model để lây index ở VT bất kỳ có ở lớp mẹ nên mọi model đều có chỉ có điều reimplement lại thôi
            //còn lấy index của cái ta chọn thì ms là lấy từ view
            standardModel->setData(index,0);//setData nếu muốn gán data là kiểu bất kỳ
        }
    }
    standardModel->setItem(1,1,new QStandardItem("21"));//dùng setItem chỉ thêm đc QStandardItem(k truyền đc số)
    standardModel->appendRow(new QStandardItem("Hieu"));//thêm cả 1 hàng
    //nếu QStandardItem ta tạo r appendRow của nó thì sẽ phân tầng và chỉ xem đc bằng tree(QStandardItemModel tạo đc tùy ý)

    //kết nối
    ui->tableView->setModel(standardModel);

    //thiết lập
    myDelegate=new ItemDelegate();
    ui->tableView->setItemDelegate(myDelegate);//itemDelegateForColumn, set riêng đc
    //tableView khi hiển thị số có tính chất là tự động hiển thị 1 cái delegate là spin box. Đó là mặc định, ta có thể chỉnh
    //lại với class riêng QItemDelegate. Ta kế thừa r chỉnh theo ý ta và dùng bằng setItemDelegate
    //khi gán setItemDelegate thì kể cả string ta cx sẽ thành delegate ta truyền vào chứ bth là chỉnh QString bằng lineEdit
}

Dialog::~Dialog()
{
    delete ui;
}

