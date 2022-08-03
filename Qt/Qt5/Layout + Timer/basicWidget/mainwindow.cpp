#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0;i<9;i++)
    {
        ui->comboBox->addItem(QString::number(i)+" item");
    }
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start(1000);
    timer->setInterval(3000);

    //bh ta muốn thủ công thêm 1 TH widget vào 1 tab, addTab lại chỉ nhận QWidget mà QLayout k kế thừa từ QWidget->cho QWidget
    //setLayout là ok thôi. Nếu ta muốn các Widget k dùng layout thì khi khai báo đơn giản truyền parent là widget tabcontent.
    //vì bản thân mỗi tab trong QTabWidget là 1 cửa sổ
    //khai báo widget mà k truyền đối số parent, và k set cho layout nào trong widget thì sẽ k hiện ra gì cả
    QLabel *label=new QLabel("Thêm thủ công");
    QLineEdit* lineEdit=new QLineEdit();
    QVBoxLayout *layout=new QVBoxLayout();
    layout->addWidget(lineEdit);
    layout->addWidget(label);
    QWidget* tabContent=new QWidget;
    tabContent->setLayout(layout);
    ui->tabWidget->addTab(tabContent,"tab thêm thủ công");//trong Qt nó đb vẫn cho QString& mà truyền trực tiếp ""
    //insertTab cho bất ky vt nào

    //bh lại muốn insertTab vào vị trí 2 1 tab y hệt cái tabContent
    //Để lấy đc cái tab khác y hệt tab cũ là cả vấn đề. Vì ta đã dùng con trỏ nên vc gán 1 biến ms bằng biến cũ cx ok nhưng
    //1 ô nhớ k thể xuất hiện 2 vị trí trên màn hình và thao tác chỉnh sửa độc lập đc. Nếu ta chuyển sang sử dụng biến value
    //thì k dùng đc luôn vì chạy hết hàm khởi tạo sẽ tự động out of scope bị xóa, nx ta phải tạo biến value ở trong file h.
    //Xong ta lại tạo ra 2 biến và gán giá trị biến này cho biến kia thì cx k đc vì diều đó chỉ đúng với kiểu dữ liệu cơ bản,
    //đây là 1 biến class mà k có operator = nên k gán đc=>sai.Vc này k chì xảy ra với tabWidget mà còn xảy ra vs nh cái khác.
    //Trong Qt Design thì đơn giản ta có thể copy và paste vs các class nhưng cx k thể copy và paste vs tabWidget
    //Cách duy nhất và an toàn nhất là tạo 1 cái mới,k có gán ghiếc gì hết và copy code y hệt là ok->code lại cả signal,slot,...

    //Cách dùng layout
    QWidget* formWidget = new QWidget(this);
    QFormLayout* formLayout = new QFormLayout(this);
    QLabel* testFormLabel1 = new QLabel("Test 1:");
    QLineEdit* testFormLabellineEdit1 = new QLineEdit(this);
    QLineEdit* testFormLabellineEdit2 = new QLineEdit(this);
    formLayout->addRow(testFormLabel1,testFormLabellineEdit1);
    formLayout->addRow("T&est 2: ",testFormLabellineEdit2);
    formWidget->setLayout(formLayout);
    ui->tabWidget->addTab(formWidget,"Form");

    QWidget* hBoxWidget = new QWidget(this);
    QHBoxLayout* hBoxLayout = new QHBoxLayout(this);
    QLabel* testHBoxLabel = new QLabel("Test 1: ");
    QLineEdit* testHBoxLineEdit = new QLineEdit(this);
    hBoxLayout->addWidget(testHBoxLabel);
    hBoxLayout->addWidget(testHBoxLineEdit);
    //nếu ta dùng QHBoxLayout or QVBoxLayout tức là nó đã specific thứ tự sắp xếp, nếu dùng QBoxLayout thì ta phải specific ở
    //hàm khởi tạo.
    //Ví dụ nếu ta dùng QHBoxLayout thì nó tự động stretch theo hàng ngang. Nó sẽ kéo dãn các widget có thể kéo để fit với chiều
    //ngang. Nếu ta muốn các widget k bị kéo dãn mà muốn nó giữ chuẩn kích thước và sắp xếp vị trí theo ý ta thì dùng
    //setAlignment, các widget sẽ k bị kéo dãn. SetAlignment sẽ cho ta set ở các vị trí đb làm cho widget của ta giữ kích thước
    //chuẩn k bị kéo dãn. Dùng thêm setStretch nếu muốn tỉ lệ(do k bị kéo dãn nên sẽ ép fit vừa cả hàng/cột nhưng thay bằng k
    //trống)
    //lineEdit có thể kéo dãn vô tận. Dựa vào 2 hàm đó là ta biến vị trí theo ý muốn r, k cần cả spacer luôn
    hBoxLayout->setAlignment(testHBoxLabel,Qt::AlignLeft);
    hBoxLayout->setAlignment(testHBoxLineEdit,Qt::AlignRight);
    hBoxLayout->setStretch(hBoxLayout->indexOf(testHBoxLabel),1);//nó thao tác với index, setAlignment có r nên setStretch k hđ
    hBoxLayout->setStretch(hBoxLayout->indexOf(testHBoxLineEdit),2);
    hBoxWidget->setLayout(hBoxLayout);
    ui->tabWidget->addTab(hBoxWidget,"HBox");

    QWidget* gridWidget = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(this);
    QLabel* testGridLayoutLabel = new QLabel("Test: ");
    QLineEdit* testGridLineEdit = new QLineEdit(this);
    gridLayout->addWidget(testGridLayoutLabel,0,0,1,1);
    gridLayout->addWidget(testGridLineEdit,0,1);
    //nếu ta set đối số 3,4 thì là column span và row span thì nó sẽ chia theo tỉ lệ. Nếu k nói rõ thì nó sẽ tự kéo line edit
    //dài hết các chỗ trống(vì line Edit có thể kéo dài vô tận còn label thì k thể kéo dài), tự chia tỉ lệ nó sẽ kéo full
    //như H/VBoxLayout
    gridWidget->setLayout(gridLayout);
    ui->tabWidget->addTab(gridWidget,"Grid");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTime()
{
    QElapsedTimer timer;
       timer.start();
    ui->label->setText("world");
    qDebug() << "test";
    qDebug() << "The operation took" << timer.elapsed() << "milliseconds";
    //QTimer cho ta một cái đồng hồ đếm thời gian để thực hiện 1 hành động gì sau 1 ktg nào đó(ta k thể lấy ra thời gian còn
    //lại QElapsedTimer, cx k thể lấy tg thực QTime, chỉ phục vụ mỗi thế thôi)->dùng để thực hiện 1 cj đó liên tục sau 1 ktg.
    //Có interval->sẽ phát timeout lt sau mỗi interval. K có interval->sau mỗi đối số start sẽ phát signal timeout
    //Cách dùng: khởi tạo,connect,start
}
