#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Khai báo model(đã khai báo view trong ui)
    strListModel=new QStringListModel(this);//truyền nv thì khi xóa this là parent nó sẽ bị xóa theo(là biến r nên vẫn v)
    QStringList strList;
    strList << "cat" << "dog" << "lizard";
    strListModel->setStringList(strList);

    //kết nối
    ui->listView->setModel(strListModel);
    ui->comboBox->setModel(strListModel);

    //set các chế độ
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed);
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //=> Cơ chế: muốn thao tác với phần tử nào trong model thì phải lấy đc index của phần tử đó, lấy cả nhiều thì list index
    //Model: chỉ cho phép thao tác số lượng phần tử chung(thêm, bớt)
    //Còn view: ms cho phép edit nội dung,chọn nội dung bên trong một cái, từng phần tử 1 đang thao tác
    //ví dụ: model ta lấy ra index của 1 row bất kỳ trong list, còn view lấy ra index của row ta đang chọn,ta đang thao tác
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //Thêm hàng mới
    int row= strListModel->rowCount();
    strListModel->insertRows(row,1);
    //Muốn thao tác vs nó thì lấy index
    QModelIndex index = strListModel->index(row);//mỗi row có 1 index. Từ index lấy row và từ row lấy index đều đc
    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
}

void Widget::on_pushButton_2_clicked()
{
    //Bh ta muốn chèn vào trong list ở 1 vị trí bất kỳ trc vị trí ta chọn=> để thao tác đc vs cj ta lấy index của nó
    //Nhớ quy luật của model,view và tính chất trên là xong.

    //lấy index của vị trí hiện tại(dùng view)
    QModelIndex currentModelIndex=ui->listView->currentIndex();
    //chèn row vào trc nó(dùng model)
    strListModel->insertRows(currentModelIndex.row(),1);//row và index đều là số có thể chuyển đổi qua nhau
    ui->listView->setCurrentIndex(currentModelIndex);
    ui->listView->edit(currentModelIndex);
}

void Widget::on_pushButton_3_clicked()
{
    QModelIndex currentModelIndex=ui->listView->currentIndex();
    strListModel->removeRows(currentModelIndex.row(),1);//removeRow
}

void Widget::on_pushButton_4_clicked()
{
    //Tuy nhiên thông thường, ng ta có 1 lớp QItemSelectionModel là 1 Model chuyên quản lý những item đc chọn lưu vào 1 model

    //lấy cái list index
    QItemSelectionModel* selection=ui->listView->selectionModel();
    //selectionModel là hàm kế thừa từ lớp mẹ QAbstractItemView cho ra QItemSelectionModel dùng khi thao tác mạnh item chọn
    QModelIndexList modelIndexList=selection->selectedIndexes();
    //QItemSelectionModel chỉ quan tâm 2 hàm currentIndex chỉ trả 1 còn selectedIndexes trả 1 list
    //nhưng rõ ràng currentIndex thì dùng luôn QModelIndex chứ cần gì thông qua QItemSelectionModel->dùng khi chọn nh

    //có index r thì chơi thôi
    //hàm data giúp trả về biến QVariant, từ đó làm bất cứ thứ j vs QVariant
    QString output="";
    foreach(QModelIndex index, modelIndexList)
    {
        QVariant variant=strListModel->data(index,Qt::DisplayRole);//đối số 2 là mục đích của vc tạo biến, đó là hiển thị
        output+=variant.toString() + "\n";
    }
    QMessageBox::information(this,"Title",output);

//cơ chế: lấy QItemSelectionModel các biến ta chọn(biến chuyên lưu item chọn)->lấy index ta chọn->lấy Qvariant làm đc mọi thứ
}

/*QAbstractItemView có các hàm chung gọi đc vs mọi view:currentIndex, model, scrollTo, setEditTriggers, setItemDelegate,
setModel, setSelectionMode, selectionModel
QAbstractItemModel:data, index, insertRows, moveRow, removeRow, rowCount, setData
=>tức là view thì mặc định luôn lấy đc vị trí ta đang chọn,lấy model đi kèm,scroll con chuột,set các chế độ,set delegate,
model,lấy QItemSelectionModel vs các thứ đã chọn->thao tác với giao diện
=>còn model thì thêm, lấy index và xóa ở 1 vị trí bất kỳ(đb thêm thì thêm đc QVariant rất mạnh),đổi vị trí->thao tác vs nd

Các view và model khác đều có các hàm nv nhưng cấu trúc có thể khác do override r. Chúng cx có những hàm khác riêng vs
từng loại: sort,expand,set cái root,...
*/
