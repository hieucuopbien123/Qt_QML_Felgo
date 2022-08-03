#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QLineEdit>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::showText);
    timer->start(5000);
    qDebug() << "set up need " << elapsedTimer.elapsed() << " ms";

    QTabWidget* tabwidget = new QTabWidget(this);
    this->setCentralWidget(tabwidget);

    QWidget* tab1 = new QWidget(tabwidget);
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    QPushButton* button1Tab1 = new QPushButton(this);
    button1Tab1->setText("Button 1");
    QPushButton* button2Tab1 = new QPushButton(this);
    button2Tab1->setText("Button 2");
    QPushButton* button3Tab1 = new QPushButton(this);
    button3Tab1->setText("Button 3");
    QSplitter* splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(button1Tab1);
    splitter->addWidget(button2Tab1);
    hLayout->addWidget(splitter);
    hLayout->addWidget(button3Tab1);
    tab1->setLayout(hLayout);
    tabwidget->addTab(tab1,"Tab 1");

    QWidget* tab2 = new QWidget(tabwidget);
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    QHBoxLayout *h1 = new QHBoxLayout(this);
    QHBoxLayout *h2 = new QHBoxLayout(this);
    QPushButton* button1Tab2 = new QPushButton(this);
    button1Tab2->setText("Button 1");
    QPushButton* button2Tab2 = new QPushButton(this);
    button2Tab2->setText("Button 2");
    QSpacerItem* spacerleft1 = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    QSpacerItem* spacerleft2 = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    QSpacerItem* spacerright1 = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    QSpacerItem* spacerright2 = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    h1->addItem(spacerleft1);
    h1->addWidget(button1Tab2);
    h1->addItem(spacerright1);
    h2->addItem(spacerleft2);
    h2->addWidget(button2Tab2);
    h2->addItem(spacerright2);
    QSpacerItem* spacerCenter = new QSpacerItem(1,10,QSizePolicy::Expanding,QSizePolicy::Ignored);//chỉnh size 1 tí
    QSpacerItem* spacerCenter2 = new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
    vLayout->addLayout(h1);
    vLayout->addItem(spacerCenter);
    vLayout->addLayout(h2);
    vLayout->addItem(spacerCenter2);
    vLayout->addWidget(button1Tab2);
    vLayout->addWidget(button2Tab2);
    tab2->setLayout(vLayout);
    tabwidget->addTab(tab2,"Tab 2");
    //nch là size vị trí ta k nên chỉnh bằng code mà dùng ui.form nếu k thì compile có thể lỗi khi resize éo fix dc

    QWidget* tab3 = new QWidget(this);
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::RightToLeft, this);
    QLabel* label = new QLabel("Label: ", this);
    QLineEdit* lineEdit = new QLineEdit(this);
    boxLayout->addWidget(label);
    boxLayout->addWidget(lineEdit);
    boxLayout->setAlignment(label,Qt::AlignCenter);
    boxLayout->setAlignment(lineEdit,Qt::AlignLeft);
    tab3->setLayout(boxLayout);
    tabwidget->addTab(tab3,"Tab 3");

    QWidget* tab6= new QWidget(this);
    QBoxLayout* Layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    QLabel* label1 = new QLabel("Label: ", this);
    QLineEdit* lineEdit1 = new QLineEdit(this);
    Layout->addWidget(label1);
    Layout->addWidget(lineEdit1);
    Layout->setSpacing(10);//cách chỉnh khoảng cách 2 các widget bên trong
//    Layout->setStretch(Layout->indexOf(label1),1);//dùng alignment thì thành kích thước default k dùng đc stretch
//    Layout->setStretch(Layout->indexOf(lineEdit1),2);
    //dùng setStretch với label là ngu dốt, dùng với button mới thấy hiệu ứng kéo dãn chứ label phần thừa dồn vào bên phải
    //thành khoảng trắng sẽ k như ý
    tab6->setLayout(Layout);
    tabwidget->addTab(tab6,"Tab 6");

    tabwidget->setCurrentIndex(2);

    QWidget* tab4 = new QWidget(this);
    QFormLayout* formLayout = new QFormLayout(this);
    formLayout->addRow(new QLabel("Name: ",this),new QLineEdit(this));//C1
    formLayout->addRow(tr("&Age:"), new QLineEdit(this));
    formLayout->setWidget(2,QFormLayout::LabelRole,new QLabel("Job",this));//C2
    formLayout->setWidget(2,QFormLayout::FieldRole,new QLabel("Description",this));
    //1 row của form chỉ đc chứa 2 widget và phải đúng là 1 LabelRole và 1 FieldRole
    tab4->setLayout(formLayout);
    tabwidget->addTab(tab4,"Tab 4");

    QWidget* tab5 = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->addWidget(new QLabel("Test: ",this),0,0);
    gridLayout->addWidget(new QLineEdit(this),0,1);
    gridLayout->addWidget(new QPushButton("Button 1", this),1,0,1,2);
    gridLayout->addWidget(new QPushButton("Button 2", this),1,1,1,1);
    //dùng grid đặc biệt là nếu dùng với các cái tự kéo dãn như lineedit thì nó sẽ tự chiếm hết. Ta set span sẽ gây lỗi
    //Nếu vs các widget bth thì span đc chứ cái này k đc. đặc biệt là grid thì các hàng các cột tự căn theo nhau
    //nếu dòng trên có 2 cột thì dòng dưới theo kích thước dòng trên và cx chỉ có 2 cột
    tab5->setLayout(gridLayout);
    tabwidget->addTab(tab5,"Tab 5");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showText()
{
    qDebug() << "Timeout";
}

