#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    qDebug() << "12";
    //vc đặt qDebug liên tục là cách hay để KT lỗi thậm chí k cần debug
    manager=new QNetworkAccessManager(this);
    target=ui->lineEdit->text();
    qDebug() << "12";
    QUrl url = QUrl::fromEncoded(this->target.toLocal8Bit());//tốt nhất là nên làm đúng qtr đổi giữa các kiểu string
    //local8bit/Latin1 chính là nói về số byte nên là QByteArray. Còn encode hay unicode hiểu là const char*/QByteArray
    if(!url.isValid())return;
    qDebug() << "12";
    QNetworkReply* reply=manager->get(QNetworkRequest(url));
    qDebug() << "12";
    //Trap qtr khi khởi tạo biến con trỏ. Nếu ta tạo biến con trỏ là thành viên của class ví dụ private chẳng hạn, sau đó
    //thì buộc phải khởi tạo bằng new. Ví dụ biến reply ở trên nếu khai báo ở private thì phải khởi tạo bằng new nhưng
    //class này lại là virtual k có hàm khởi tạo nên buộc phải khởi tạo ở trong hàm khác(k là biến tv)
    //=> nhờ v ta mới dùng đc reply về sau, nếu là tv biến class, k khởi tạo new sẽ lỗi memory ngay khi sử dụng

    //bất cứ cái gì có khả năng dùng signal slot thì buộc dùng con trỏ để tránh lỗi
    connect(manager,&QNetworkAccessManager::finished,this,[&](QNetworkReply* reply)//dùng lamba thì buộc k dùng SIGNAL
    {//lamba buộc có capture [&]
        qDebug() << "1";
        QByteArray data=reply->readAll();
        //trừ khi abort or close biến reply, nó sẽ luôn luôn trong TT sẵn sàng để đọc or sử dụng ở trong hàm này và có thể
        //lấy bằng read or readAll. Cụ thể nếu k gọi hàm read từ signal readyRead thì dùng readAll sẽ lấy toàn bộ content
        QString str=QString::fromLatin1(data);//nắm vững mấy cái đổi này đi
        ui->textEdit->setPlainText(str);//setHtml và setPlainText là specific of setText

        //        QPixmap pixmap;
        //        pixmap.loadFromData(reply->readAll());//byteArray có thể lưu định dạng ảnh còn QString thì k
        //        ui->label->setPixmap(pixmap);
    });
    connect(manager, &QNetworkAccessManager::finished, manager, &QNetworkAccessManager::deleteLater);
    //mặc dù khi kết thúc Ct thì con trỏ tự bị xóa nhưng nếu Ct dài thì nên deleteLater cho chắc

    connect(manager,SIGNAL(sslErrors(QNetworkReply*,const QList<QSslError>&)),
            this,SLOT(showSslErrors(QNetworkReply*,const QList<QSslError>&)));
    //reply cx có signal kiểm tra lỗi về ssl, và cần kiểm tra lỗi kết nối nx(lỗi ssl và lỗi bản thân biến reply)
    connect(reply,SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
            this,SLOT(showReplyErrors(QNetworkReply::NetworkError)));
    if(reply->error()!=QNetworkReply::NoError)
    {
        qDebug() << "Error: " << reply->error();//kiểm tra luôn khởi tạo ok k khỏi chờ loop sau
        return;
    }
    qDebug() << "Error: " << reply->errorString() << QSslSocket::supportsSsl();
    //đây là ta KT lỗi ngay cứ in ra những thứ mà đáng lẽ phải k có lỗi j ngay từ đầu; còn connect là khi có lỗi gì
    //xảy ra thêm trong qtr thôi. Dùng nv or dùng Đk như trên cx đc
    //reply là hàm con của QIODevice, mà QIODevice mở ra vô số hàm chức năng khác như đọc, gán, lấy lỗi, kiêm tra TT,...
    //=> reply như 1 Device lưu reply v. UnknownError là ok éo có errors

    qDebug() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
    //KT version của ssl dùng trên máy(1 class rieng QSslSocket)

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(State(qint64,qint64)));
    //diễn tả qtr
    qDebug() << "13";
    reply->waitForReadyRead(2000);//block signal cho đến khi readyRead, tg chưa hết mà read xong thì cx end trả về 1
    reply->deleteLater();//nên dùng trong vòng event loop

    qDebug() << "14";
    //bản chất hàm deleteLater là để chắc chắn 1 biến j đc xóa đi về sau khi sử dụng. Cơ chế: khi hàm này đc gọi, nếu biến
    //gọi hàm đc xử lý trong 1 eventloop trc main loop thì khi 1 cái loop kết thúc thì biến sẽ bị xóa. Còn nếu biến này k
    //nằm trong cái loop nhỏ nào trc khi bước vào event loop thì biến sẽ bị xóa ngay khi cái main loop start. Do đó ta gọi
    //hàm như này mà k dùng QEventLoop bên dưới thì chả làm cái éo j, ngay lần chạy đầu tiên từ trên xuống gặp exec nó
    //bị xóa luôn quá nhanh chưa kịp finish. Còn nếu dùng eventLoop-> nó sẽ chờ reply nó finish r ms exit loop-> mà finish
    //thì ta đọc mẹ nó luôn r, do biên dịch theo thứ tự nên hoàn thành xong slot, lúc đó reply ms bị xóa cx k còn qtr nx
    //Cx vì nv nên bên trên ta deleteLater là slot của QNetworkAccessManager sau khi finish=> khi finish gọi hàm này, ngay
    //vòng mainloop sau nó bị xóa luôn=> dùng hàm này để chắc chắn các biến sẽ bị xóa ở lần sau k cần chờ hết Ct
    //dùng ở đây là thừa vì khi QNetworkAccessManager bị xóa thì reply cx xóa luôn mnr, test thôi
    //thậm chí chỉ vì muốn deleteLater mà tạo biến QEventLoop chỉ connect cho nó quit k thôi cx ok, MĐ là dùng đc hàm này
    //deleteLater ở trong thread thì thread kết thúc nó sẽ xóa. Còn bth thì nó sẽ bị xóa khi CÁI BẤT CỨ 1 CÁI LOOP NÀO
    //CHỨA NÓ START 1 VÒNG MỚI.Trên thì nó chỉ ở trong mainloop=>mainloop start vòng ms là nó bị xóa
    //=>lỗi: gọi loop exec ở sau hàm exec của main=> vòng loop sẽ kbh bị xóa(k gọi hàm exit)

    QEventLoop loop;
    connect(reply,SIGNAL(finished()),this,SLOT(testFinished()));//k nên dùng deleteLater như ở trên, mà nên dùng
    //trong vòng loop này để khi ra ngoài loop này xóa luôn kbh nhầm; để ở trên thì vòng loop lớn bắt đầu ms xóa như này:
//    connect(reply,SIGNAL(finished()),reply,SLOT(deleteLater()));
    qDebug() << "15";
    //hàm finished() của QNetworkReply* phát ra khi kết thúc xử lý yêu cầu, biến này sẽ k còn update dữ liệu j nx
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec(QEventLoop::AllEvents);//có thể lọc loại event

    //event loop là cái vòng lặp sẽ tự động nhét các sự kiện trc hàm exec vào trong và thực hiện bên trong. Có thể thấy
    //hàm exec() của QApplication cx tạo ra 1 vòng lặp tương tự kiểm soát event của toàn bộ CT gọi là main loop thực hiện
    //main thread. Nv, phần code đằng sau exec sẽ k bị thực hiện cho đến khi ta gọi exit(return code)=> nếu cho exec() vào
    //hàm khởi tạo mà k exit thì hàm exec lớn ở file main sẽ éo đc thực hiện luôn mà phải chờ nó exit đã, tệ hơn là cho vào
    //trc hàm show thì hàm show k chạy cho đến khi exit do qtr thực hiện từ trên xuống dưới.
    //Vai trò: khi ta cần thực hiện event gì(connect chẳng hạn) mà lại muốn chờ nó thực hiện xong thì mới bắt đầu các event
    //phía dưới(thg là các event buộc thực hiện và nó cần quá trình để thực hiện xong ms dùng đc các cái bên dưới)
    //hàm quit() = exit(0) ms dùng đc cái bên dưới. Ta có thể dùng thread exec vs cơ chế tương tự nhưng tối ưu hơn vì độc lập
    //K cần dùng con trỏ vì exec tự ép vào vòng, nếu muốn xóa biến ngay sau khi exit thì có thể khai báo pointer để delete
}

void Widget::State(qint64 sent,qint64 total)
{
    qDebug() << "sent: " << sent << " Total: " << total;
}

void Widget::testFinished()
{
    QNetworkReply* reply=qobject_cast<QNetworkReply*>(sender());
    //hàm sender sẽ giúp ta xử lý vấn đề lấy object phát signal vì nh hàm signal k có biến đối số cần dùng
    qDebug() << reply->isFinished() << "_" << reply->url();
    //dùng biến reply ntn cx đc sau khi có hết dữ liệu r
}

//Giả sử ta dùng deleteLater(đáng lẽ k dùng thì ok nhưng cứ thích dùng)-> ta chạy eventloop như v và new vs connect
//manager ngay trong hàm khởi tạo, và để chắc chắn, ta muốn deleteLater cái manager khi hoàn thành vc download. Gặp lỗi
//vì ta muốn ấn nút thì lấy liên tục cơ, mà ta deleteLater khi finish nên khi finish phát vòng exec sau, nó bị xóa luôn.
//thì ta ấn nút tiếp k get nx mà trả về lỗi, lúc này manager trỏ vào vùng nhớ chưa cấp phát=> để dùng thì ta phải khai báo
//biến manager khi ấn nút tiếp=> nhét hàm khai báo vào bên trong slot ấn nút thì cứ ấn là có=> lỗi tiếp vì ta vẫn để hàm
//connect của manager ở hàm khai báo tức là nó khai báo hàm connect signal slot của biến mà còn chưa cấp vùng nhớ là lỗi.
//Để khắc phục, nhét toàn bộ hàm connect đó vào trong hàm slot bấm nút=> gặp lỗi tiếp nếu đặt ở sau exec() của event
//loop. NN là vì sau khi reply nó finish-> hàm connect vẫn chưa đc gọi-> eventloop kết thúc ngay sau đó->trình biên dịch
//kéo xuống thấy loop kết thúc xóa mẹ nó biến, lúc đó connect k bh đc sử dụng=>cuối cùng nó vẫn k đc
//thực hiện-> ở vòng loop sau ngay khi main loop start thì biến bị xóa mnr, lúc đó signal slot đi kèm biến cx bị xóa theo
//và ta ấn nút tiếp thì lại tiếp tục nv=> đặt connect ở trc exec là xong
//Điều này đặt ra cho ta những quy tắc: hàm khởi tạo của class chính nên để gọi gàng như main.cpp; hàm khởi tạo này chỉ
//cần khởi tạo và connect các biến mặc định mà thôi; nếu biến đó mà có nhu cầu dùng đi dùng lại nh lần=> thì k khai báo
//biến đó con trỏ ở trong hàm khởi tạo khi ta dùng connect deleteLater(vì với các Ct lớn ta thg dùng deleteLater). Nếu k
//dùng deleteLater thì k cần; Các chức năng ta tốt nhất là nhét tất cả vào 1 slot riêng-> và khai báo biến hay làm gì
//đều trong slot đó, cứ ấn hay làm gì thì tất cả các chức năng thực hiện trong class đó để làm gọn hàm khởi tạo(nên
//dùng deleteLater cho chuẩn khi làm nv)
//=> viết 1 chức năng cho Ct: tạo 1 slot lớn bao gồm hàng loạt các slot nhỏ thực hiện chức năng; tạo các biến và xử lý;
//deleteLater khi dùng xong vs tư duy là vòng loop sau sẽ bị xóa ngay

//còn nx: nếu Ct chạy hàm connect sau khi phát signal thì sẽ k chạy hàm connect đó, vì signal đơn giản chỉ phát ra có 1 lần
//vào 1 lúc nào đó-> ta phải cho connect signal trc khi phát ra signal->hàm connect có hiệu lực ngay sau khi Ct chạy đến nó,
//nó sẽ rình mọi signal đến vs biến đó cứ trùng singal vs nó là quất
//=>deleteLater sẽ xóa biến khi vòng loop chứa nó bắt đầu exec 1 vòng mới->tức là bên trên ta để hàm connect sau exec nó k
//thực hiện kp vì biến đã bị xóa->sai lầm mà là dó signal finish nó phát ra có 1 lần và chưa gặp hàm connect nên k bắt đc
//và vòng sau bị xóa mất, chứ kp là finish r thì nó mãi mãi phát ra signal finish k ngừng nghỉ, nó phát mỗi 1 lần
//Thứ tự trong thực tế: ấn nút->máy compile sẽ chạy theo thứ tự từ trên xuống->gặp hàm get lưu lại vào stack->gặp tất cả các
//hàm connect cx lưu lại vào stack->gặp loop exec-> thực hiện các hàm trong stack đến khi gặp quit thì thôi->thực hiện get->
//thực hiện các slot bắt đc->finish->exec kết thúc lại đi xuống=>điều hay là gặp exec thì các hàm nó lưu ms thực hiện

void Widget::showSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    foreach(QSslError error,errors)//lúc nào cx có 1 lớp riêng quản lý error
    qDebug() << "Error" << error.errorString();
}

void Widget::showReplyErrors(QNetworkReply::NetworkError error)
{
    if(error!=QNetworkReply::NoError)
        qDebug() << "Error: " << error;
}

//để truy cập vào https, phải tải openssl về->chạy ở win32->thêm 4 cái lib vào như file pro trỏ đến openssl
