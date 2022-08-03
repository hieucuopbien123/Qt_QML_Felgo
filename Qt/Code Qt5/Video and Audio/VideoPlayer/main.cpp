#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMediaPlayer* player = new QMediaPlayer;//kp là 1 widget-> k có giao diện-> chơi audio k cần giao diện, nhưng video..
    QVideoWidget* videoWidget = new QVideoWidget;//1 widget giúp chạy vid

    player->setVideoOutput(videoWidget);
    player->setMedia(QUrl::fromLocalFile("B:\\Qt\\newGeneration\\MyPlayer\\VideoPlayer\\vid\\vid.m4v"));

    videoWidget->setGeometry(100,100,300,400);//widget k set thì k hiện
//    videoWidget->setFullScreen(true);
    videoWidget->show();
    player->play();//có thể dùng vào slot ấn thì chạy

    //Tạo widget chạy vid->gán widget vào player->bây h cái player của ta chỉ thao tác với video->gán vid cho nó->chạy player

    qDebug() << player->state();

    return a.exec();
}
