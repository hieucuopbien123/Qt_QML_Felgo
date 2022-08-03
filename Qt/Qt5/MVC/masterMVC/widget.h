#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QStringListModel* strListModel;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
/*Kiến trúc MVC: Mô hình quản lý dữ liệu Model-View-Controller cho phép ta thao tác với dữ liệu và hiển thị nó 1 cách trực tiêp
có lợi hơn rất nhiều so với mô hình item-base nếu ta muôn hiển thị 1 lượng dữ liệu lớn cũng như thao tác bên trong.
Trong Qt, thì controller đc đính kèm với View, ta thao tác đổi dữ liệu vs 1 view thì dữ liệu sẽ bị đổi và hiển thị ngay ở các
view khác đc kết nỗi với cùng model.
Có nh loại view và nh model khác nhau và bất cứ loại nào cũng có thể truy cập đc vào cái còn lại nhưng để hiển thị đc tốt nhất
thì là QStringListModel-QListView/QDirModel-QTreeView để đảm bảo toàn bộ dữ liệu đc hiển thị
Cơ chế:nếu là item-base thì chỉ cần khai báo item và widget hiển thị r add vào là xong; với MVC(trong qt) thì khai báo model(có
data),view và setModel cho view là xong.(các widget hiển thị của item base cx dùng đc như view của MVC)
Các loại model:QStringListModel,QFileSystemModel,QDirModel,QStandardardItemModel,QItemSelectionModel...
Các loại view:QTreeView,QListView,QComboBox,QTableView,QHeaderView,QColumnView...

QAbstractItemView là lớp mẹ của các view cx lưu các loại cờ thao tác với item, bao gồm vc chọn nh hay ít, và cung cấp các hàm
chung cho mọi View: lấy biến QItemSelectionModel để thao tác vs các biến chọn dễ hơn, hay set chế độ edit cho model,setdelegate
QItemSelectionModel thao tác với các item đã chọn
QModelIndexList và QModelIndex bắt buộc để lưu các index khi thao tác các phần tử
QHeaderView thao tác với header hiển thị

QDirModel QFileSystemModel thao tác với hệ thống file trong máy, QStringListModel thao tác các đối tượng string ta tự thêm vào,
QStandardardItemModel thao tác với các item bất kỳ ta tự tạo

QListView QComboBox hiển thị theo dòng(cột cx chỉ là dòng in lệch vị trí); QTableView bảng; QTreeView hiển thị phân tầng
QColumn View cx là 1 kiểu hiển thị theo cột kiểu TQ cx tương tự thôi
*/
