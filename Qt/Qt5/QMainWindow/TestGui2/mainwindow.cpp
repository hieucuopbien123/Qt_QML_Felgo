#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label=new QLabel();
    proBar=new QProgressBar();
    proBar->setTextVisible(false);

    ui->statusbar->addPermanentWidget(label);
    ui->statusbar->addPermanentWidget(proBar);
    label->setText("Hello");
    //khi ta showMessage thì nó sẽ hiện ra message bên trái 1 lúc theo timeout, default sẽ hiện mãi mãi
    //(addPermanentWidget thì các widget sẽ tồn tại vĩnh viễn, nằm dồn sang bên phải theo thứ
    //tự. Còn addWidget thì sẽ tạo widget tạm thời và biến mất khi có showMessage đè lên, các widget tạm thời sẽ
    //dồn sang bên trái).add các widget sẽ có đối số stretch là tỉ lệ trên thành statusBar full kín=> Trap: nếu
    //addPermanentWidget mà có stretch thì nó sẽ tự full kín statusbar khiến message kbh hiện ra đc
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDo_Sth_triggered()
{
    ui->statusbar->showMessage("hello",2000);//qtr là cái này và addWidget
    proBar->setValue(50);
}
