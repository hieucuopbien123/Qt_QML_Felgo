#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);//chuyên play media, cả vid và au. Mặc định là chạy au
    qDebug() << "Duration: " << player->duration();
    connect(player,&QMediaPlayer::positionChanged,this,&Widget::on_positionChanged);
    connect(player,&QMediaPlayer::durationChanged,this,&Widget::on_durationChanged);
    //signal duration changed hiện ra mỗi khi player đc load vào 1 mp3 có độ dài mới, ban đầu độ dài là 0.
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}

void Widget::on_horizontalSlider_2_sliderMoved(int position)
{
    player->setVolume(position);
}

void Widget::on_pushButton_clicked()
{
    player->setMedia(QUrl::fromLocalFile("B:\\Qt\\newGeneration\\MyPlayer\\MyPlayer\\au\\au1.mp3"));
    //file audio k dùng đc resource mà là đường dẫn tuyệt đối
    //setMedia sẽ set cái nguồn media 1 là QMediaContent(dùng tạo từ QUrl cx đc), 2 là stream QIO nhưng mặc định nullptr.
    //Nếu ta có 1 QIODevice thì dùng, khi đó url 1 sẽ cung thêm thông tin về media.
    //Với QUrl ta có thể dùng đc 1 file tren internet or fromLocalFile
    player->play();
    qDebug() << player->errorString();//in ra lỗi ví dụ máy k có codec mp3 chẳng hạn
}

void Widget::on_pushButton_2_clicked()
{
    player->stop();
}

void Widget::on_positionChanged(qint64 position)
{
    ui->horizontalSlider->setValue(position);
}

void Widget::on_durationChanged(qint64 position)
{
    ui->horizontalSlider->setMaximum(position);//muốn dùng slider hay progressBar phải xét max nó là gì đã
//    ui->horizontalSlider_2->setValue(player->volume());
    //default volume là 100 của player và là maxvolume với âm lượng máy tính hiện tại(Ta chỉ có thể chỉnh từ đây giảm xuống)
    //Cho nên ta set max 100 là cx đc r. Set max là đc dù vị trí ban đầu ở đâu thì cx k qtr vì âm lương tự chỉnh r.
    //Giả sử nếu vị trí bđ bị sai, thì phải setVolumn ở đây theo vị trí ban đầu mới đúng, ai lại set cho slider theo âm
}
