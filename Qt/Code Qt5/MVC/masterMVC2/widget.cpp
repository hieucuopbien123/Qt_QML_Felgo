#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //khai báo
    dirModel=new QDirModel();
    dirModel->setReadOnly(false);

    //QFileSystemModel lợi hơn ở chỗ đồng bộ trực tiếp với hệ thống vd ta xóa hay tạo mới trên hệ thống thì nó cập nhật ngay
    //tức khắc(nó dùng 1 thread riêng để duyệt file nên k ảnh hưởng tới main thread khi thao tác)->nên dùng thế ht QDirModel
    systemModel=new QFileSystemModel();
    systemModel->setRootPath("");//sẽ là root máy tính->chỉ cần có lệnh này là còn lại y hệt QDir
    //khi dùng QFileSystemModel thì cx có 1 lỗi là treeView k dùng đc resizeColumnToContent(0);
    //ta thay thế bằng lệnh sau: ui->treeView->header()->setResizeMode(0, QHeaderView::ResizeToContents);
    //Quản lý header có 1 class View riêng là QHeaderView truy cập bằng header()=>setResizeMode truyền mỗi marco sẽ fit tất cả
    //=>dùng header view của tree vỉew. Thao tác với view như chỉnh căn lề,..

    //kết nối
    ui->treeView->setModel(dirModel);
    ui->treeView->setRootIndex(dirModel->index("/"));
    //cái dirmodel khác với QDir. QDir thì "" sẽ ra root Ct, "/" là root ổ cứng(luôn v).->ký hiệu "/" luôn là root of máy
    //Nhưng cái dirmodel là ta thao tác với toàn bộ cây thư mục máy tính chứ kp thư mục hiện tại nên "" hay "/" đều là nguồn max

    //set các chế độ và các thao tác với toàn bộ
    dirModel->setSorting(QDir::DirsFirst | QDir::Name | QDir::IgnoreCase);
    QModelIndex index=dirModel->index("B:/");
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(0);//chỉ đc vs QDir
    //muốn chỉnh cj chuẩn thì phải biết trc, tưởng tượng trc đc những gì cần diễn ra và viết các hàm thục hiện lần lượt

    //thao tác
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //lấy index
    QModelIndex index=ui->treeView->currentIndex();
    if(!index.isValid()){ return; }

    //có index r thì chơi thôi
    QString name=QInputDialog::getText(this,"Name","Input: ");//QInputDialog nhập 1 QString bất kỳ,dùng khi cần lấy bcứ lúc nào
    if(name.isEmpty()){ return; }
    dirModel->mkdir(index,name);
}

void Widget::on_pushButton_2_clicked()
{
    //lấy index
    QModelIndex index=ui->treeView->currentIndex();
    if(!index.isValid()){ return; }

    //chơi luôn
    if(dirModel->fileInfo(index).isFile())//lấy đc thông tin kiểu QFileInfo nè
    dirModel->remove(index);//chỉ xóa file
    else
    dirModel->rmdir(index);
}
