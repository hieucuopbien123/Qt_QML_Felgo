#include "itemdelegate.h"

ItemDelegate::ItemDelegate()
{
    //mở rộng ra có thể dùng lineEdit cho QString cx ok cứ muốn edit item bằng cj thì tạo item delegate nv
}

QWidget* ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox * spinBox=new QSpinBox(parent);
    spinBox->setRange(-1,100);
    return spinBox;
    //luồng(ấn vào ô-> chỉnh spinbox->click ra ngoài): lấy giá trị từ table gán vào spinbox, lấy Gt spinbox gán vào table
    //editor là cái spinbox ta chỉnh;index là index của ô chọn trong table;option là lưu các thuộc tính của từng item trong
    //table có index là đối sô index như vị trí,icon,font;parent cx như option nhưng nó coi mỗi item là 1 widget và cx lưu
    //thuộc tính các widget đó;model là cả cái table
}

void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //lấy số từ model
    int value=index.model()->data(index,Qt::EditRole).toInt();//chuyển đc từ index sang model cx như từ model lấy index
    //Nhớ Th này dùng Qt::EditRole
    //truyền vào spinbox
    QSpinBox* spinBox=static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)const
{
    //lấy số từ spinbox
    QSpinBox* spinBox=static_cast<QSpinBox*>(editor);
    spinBox->interpretText();//hàm này có tác dụng là compille cái text trong spinBox->đảm bảo lấy GT mới nhất của spinBox
    int value=spinBox->value();
    //gán gt cho model
    model->setData(index,value);
}

void ItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    editor->setGeometry(option.rect);
}
