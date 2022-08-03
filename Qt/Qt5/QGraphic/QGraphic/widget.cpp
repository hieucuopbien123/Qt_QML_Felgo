#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(6);

    ellipse = scene->addEllipse(10,10,100,100,blackPen,redBrush);
    rect = scene->addRect(-100,-100,50,50,blackPen,blueBrush);
//    ui->graphicsView->setSceneRect(-100,-200,300,600);
//    scene->setSceneRect(-200,-200,600,200);

    rect->setFlag(QGraphicsItem::ItemIsMovable);//view hiển thị center màn hình là (0,0) mặc định
    //giống MVC nhưng là graphic view và scene. Ta điều khiển model như là painter vẽ cj vào model.Lấy các hình vẽ bằng
    //các class item. Còn điều khiển view với class view

    square = new mySquareItem();
    scene->addItem(square);

    QPen myPen(Qt::red);
    QLineF bottomLine(scene->sceneRect().bottomLeft(),scene->sceneRect().bottomRight());//QLineF lưu thông tin 1 đth
    scene->addLine(bottomLine,myPen)->setFlag(QGraphicsItem::ItemIsMovable);//set đc luôn trong lúc add
    //k cần lấy biến QGraphicsLineItem
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->graphicsView->rotate(5);
}

void Widget::on_pushButton_2_clicked()
{
    ui->graphicsView->rotate(-5);
}
