#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(2);
    QTreeWidgetItem *item1=new QTreeWidgetItem();
    QTreeWidgetItem *item2=new QTreeWidgetItem();
    item1->setText(0,"Tree item 1 ");
    item2->setText(0,"Tree item 2 ");
    item2->setText(1,"Content of item 2");
    ui->treeWidget->addTopLevelItem(item1);
    item1->addChild(item2);

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//nó dùng đc của view bth, nhưng k thao tác lấy ra đc
    ui->listWidget->addItem("List Item 1");
    ui->listWidget->addItem("List Item 2");//addItems(QStringList) cx phổ biến

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setItem(1,1,new QTableWidgetItem("table item 1"));
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("table item 2"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str("");
    if(ui->listWidget->currentItem()!=nullptr)
    {
        str+=ui->listWidget->currentItem()->text();
    }
    if(ui->treeWidget->currentItem()!=nullptr)
    {
        str+=ui->treeWidget->currentItem()->text(0);
    }
    if(ui->tableWidget->currentItem())//thất bại trả ra null thì có khác gì bằng 0 đâu, mọi biến con trỏ khác đều là bool 1
    {
        str+=ui->tableWidget->currentItem()->text();
    }
    //chú ý currentItem nó k bắt lỗi nullptr, nếu currentItem là nullptr mà ta vẫn cố lấy text thì sẽ bị lỗi crash Ct
    //luôn có tư duy kt liên tục, làm như này có chắc chắn sẽ xảy ra cái này k ms đi tiếp
    QMessageBox::information(this,"Title",str);
}
