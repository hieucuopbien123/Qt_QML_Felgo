#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QItemDelegate>
#include <QSpinBox>

class ItemDelegate : public QItemDelegate
{
public:
    ItemDelegate();
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //QItemDelegate là 1 class xử lý riêng vc chỉnh sửa cái delegate của QTableView khi hiển thị. 4 hàm này là slots đc kết
    //nối sẵn vs signal ở tầng thấp. Khi chỉnh sửa sẽ tự động phát các signal làm đúng 4 chức năng này nhưng QItemDelegate
    //k làm gì cả nên ta phải override
};

#endif // ITEMDELEGATE_H
