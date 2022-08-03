#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
    this->setCentralWidget(videoWidget);

    slider = new QSlider(this);
    progressBar = new QProgressBar(this);
    slider->setOrientation(Qt::Horizontal);
    ui->statusbar->addPermanentWidget(slider);
    ui->statusbar->addPermanentWidget(progressBar);

    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(player,&QMediaPlayer::durationChanged,progressBar,&QProgressBar::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,progressBar,&QProgressBar::setValue);

    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);
    //slider có signal valueChanged khi đổi giá trị, còn sliderMoved phát khi ng dùng move nó(giá trị cx đổi).
    //=>2 cái khác nhau.Ví dụ nếu dùng valueChanged ở trên thì video chạy mà ta k drag value cx change->VD ở đây khi đổi
    //nó lại phát signal->chạy slot move vị trí đó,thành ra nó bị move lại vị trí cũ gây hiện tượng giật->cần dùng đúng
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open a file","", "Video File(*.m4v *.mp4 *.avi)");
    //chú ý phân cách các filter là khoảng trăng
    on_actionStop_triggered();

    player->setMedia(QUrl::fromLocalFile(filename));

    on_actionPlay_triggered();
}

void MainWindow::on_actionPlay_triggered()
{
    player->play();//play này k start từ đầu mà chạy tiếp từ cái pause.Trừ khi ta truyền lại file set từ đầu cho nó sẽ thành start
    ui->statusbar->showMessage("Playing",2000);
    //cái statusbar ở trong gui của QMainWindow
}

void MainWindow::on_actionPause_triggered()
{
    player->pause();
    ui->statusbar->showMessage("Pause");
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    ui->statusbar->showMessage("Stop");
}
