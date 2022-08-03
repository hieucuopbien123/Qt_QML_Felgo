#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("DESKTOP-GN3V8MM\\SQLEXPRESS");
    db.setDatabaseName("mydsn32");
    db.open();

    model1=new QSqlQueryModel(this);//model chuyên thực hiện query, k sửa đc trực tiếp trên bảng
    //giống QSqlQuery nhưng kết quả của nó hiện ra ở view connect vs model
    model1->setQuery("SELECT [Name],[Age]FROM [dbo].[Table1]");
    ui->tableView->setModel(model1);

    model2=new QSqlTableModel(this);//nó sẽ hiển thị table của database và sửa đc
    model2->setTable("Table1");//gán table cho model tức là có cái header(k có giá trị)
    model2->select();//gán các gia trị bên trong table đã gán cho model
    ui->tableView_2->setModel(model2);

    model3=new QSqlRelationalTableModel(this);
    model3->setTable("Table1");
    model3->setRelation(1,QSqlRelation("relationTable1","Age","Salary"));//chỉ đc thế 1 cột bằng cột nào mà thôi
    //cột phải cùng kiểu vd: cột 0 của table là cột name string k thể thể bằng salary int đc nên phải truyền số 1
    model3->select();
    ui->tableView_3->setModel(model3);

    qDebug() << model3->lastError().text();//lastError trả về QSqlError cho ta lỗi
    qDebug() << model1->query().lastQuery();//lấy từ model->querry và ngc lại đều ok//hàm lastQuery giúp lấy dạng string
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

