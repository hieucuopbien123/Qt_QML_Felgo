#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    job = new MyJob();
}

Widget::~Widget()
{
    delete job;//k có this ở khai báo thì phải delete
    emit onStop();//nếu k tắt thì cái QtConcurrent::run() k thể cản
    //Tắt Ct chính thì run kết thúc. Làm v để fix lỗi QtConcurrent còn job thì cx phải xóa đi. Thế là hết chả còn j phải lo.

    //Chú ý: Khi Ct kết thúc thì đúng là Qt tự động xóa nhưng chỉ là xóa vào biến cục bộ, chứ k chủ động
    //xóa con trỏ. Nên từ trc tới h ta sai. Khi khai báo con trỏ trong Ct ở bất cứ đâu đều phải tự xóa
    //Khi nào ta dùng xong thì ta xóa bằng deleteLater() nhưng nếu ta tắt Ct thì sao? Chắc chắn deleteLater sẽ không hoạt động
    //vì nó éo chạy vòng sau nx. Khi đó ta phải fix bằng cách dùng delete. Dù dừng Ct thì mọi biến con trỏ đều tự bị xóa nhưng
    //ta k nên phụ thuộc vào Ct tự xóa do kết thúc. Như v nếu dùng con trỏ-> 1 là chủ động xóa, 2 là khai báo parent là this để
    //this xóa nó cx bị xóa.
    //Nếu ta khai báo biến job cục bộ. Ct kết thúc job sẽ tự bị xóa->dù con trỏ hay kp con trỏ sẽ đều gọi destructor
    delete ui;
}


void Widget::on_startButton_clicked()
{
    connect(job,&MyJob::onNumber,this,&Widget::newNumber);
    connect(this, &Widget::onStop, job,&MyJob::stop);
    //nếu job là biến con trỏ thì phải khai báo new trc khi dùng nếu k sẽ lỗi

    QFuture<void> test = QtConcurrent::run((this->job),&MyJob::start,QString("kitten"));//con trỏ đối tượng, hàm, đối số
    //QtConcurrent là namespace, run là hàm làm 1 hàm nào chạy ở trong thread riêng biệt lấy ra từ global threadpool.
    //Nhớ rằng func nó k chạy ngay lập tức mà phải đảm bảo threadpool có thread available thì mới chạy
    //QFuture là thứ lưu kết quả của tính toán bất đồng bộ. Ta có thể kiêm tra trạng thái của vc tính toán đó như isFinished(),
    //isCanceled() or chủ động begin(), cancel()

    //Lưu ý: ta biết là nó chạy trên thread riêng biệt lấy từ threadpool, và nó run khi trong threadpool có thread available
    //Tức là nó k đảm bảo là mỗi lần có run là nó sẽ chạy trên 1 thread hoàn toàn khác. Do Ct chạy quá nhanh nên chung 1 thread
    //có thể làm 2 task sequentially. Miễn là thấy thread pool trống là nó nhảy vào, đồng nghĩa đang thực hiện task này,có
    //khoảnh khắc nó rảnh thì lại thực hiện cái kia luôn, nhanh đến độ chỉ cần 1 thread. Ta dùng msleep sẽ làm nó chạy chậm lại
    //và khoảng thời gian chờ đó yêu cầu cái thread k thể tiếp tục nên sẽ thấy nó thực hiện đc ở 2 thread khác nhau. Nếu dùng
    //thêm 1 hàm run nx.

    //pb: QObject có thread() in ra thread của object đó cx như QThread::currentThread() sẽ lấy ra thread hiện tại-> trả về biến
    //QThread* đang quản lý cái thread hiện tại. Còn QThread::currentThreadId() sẽ trả về cái handle của thread hiện tại.
    //QT::HANDLE thực ra là void* thôi. 2 biến chạy 2 thread khác nhau luôn có Id khác nhau, còn biến QThread*thread() thì có
    //thể giống nhau, vì biến nó lưu 2 cái handle khác nhau đc.

    //Khi ta tắt Ct chính thì mọi biến tự động xóa. Nếu job là biến cục bộ: job sẽ tự bị xóa nhưng cái thread vẫn chạy qDebug()
    //đây là 1 lỗi của thread ta phải tự fix bằng cách viết đk cho nó dừng lại. Đó là một lỗi của QtConcurrent khi kết thúc Ct
    //chứ k lq j đến biến job còn tồn tại hay k. Dù xóa nó rồi nó vẫn chạy thread. Đó là tính năng k thể cản của hàm run thôi

    //K cần dùng thread, mutex nx-> cứ run nó + xử lý điều khiển nó dừng để tắt đi ngừng chạy là xong.
    //Vc chạy 1 hàm bắt signal đến 1 hàm khác đáng lẽ phải có queue hay direct nhưng 2 thread khác nhau thì lo gì, 1 ô phát thì
    //ô kia bắt r rảnh thì chạy luôn
}

void Widget::on_stopButton_clicked()
{
    emit onStop();
}

void Widget::newNumber(QString name, int number)
{
    qDebug() << "From dialog: " << name << " " << number << " " << QThread::currentThreadId();
    ui->lineEdit->setText(name + " " + QString::number(number));
}
//Các lỗi của app này:1>job là 1 thành viên trong mainthread và ta lại dùng run hàm start ở thread khác trong threadpool. Dù
//QtConcurrent tốt nhưng k phải là catch-all nên vẫn có thể deadlock. Ví dụ nếu biến job bị xóa trc khi hàm start kết thúc thì
//Ct sẽ stop working và unexpected finish->thử chủ động delete nó là thấy-> fix bằng cách cho nó static func và stop là biến
//static. Khi đó thì hàm k còn phụ thuộc vào biến job nx. Dù delete k còn instance vẫn chạy đc.
//2>stop k là biến atomic. Mà ta có 2 thread chẳng hạn start ở thread này và stop ở thread main cùng gọi vào nó thì toang. Ta
//nên để cái stop là atomic or dùng mutex. QAtomicPointer or QAtomicInt trong qt.QtConcurrent cho ta biến 1 hàm thành độc lập nv
//3>biến test ta k sử dụng, nó là kết quả trả về. Nếu ta sử dụng thì có thể gây sai sót-> ta phải block khi start chạy. Khi
//cái kết quả nó available mới đc dùng kquả biến test.Mà để là cục bộ trong hàm thì sử dụng sao đc.Phải để nó là biến thành viên
//4>Mỗi lần ấn start thì 1 hàm run lại chạy-> 1 hàm job gọi nhiều hàm run trong các thread khác nhau. Ấn stop thì nó dừng cả
//Ct của ta phải expected là chạy 1 hàm start thôi mới chuẩn.
//Ta cần: tạo ra 1 hàm static hoặc 1 hàm tự do hoàn toàn k dùng đến các biến phụ thuộc ở thread khác, nhớ là nó phải có giá trị
//trả về ví dụ QString-> gọi run với nó nhưng kết quả trả về QFuture<QString> là biến thành viên của class-> Dùng QFutureWatcher
//có signal finished để xác định nếu run chạy xong r mói đc dùng cái result->ấn start tiếp thì phải chờ cho nó kết thúc or dừng

//Khi làm vc với thread cần chú ý: mục đích của ta thường là ví dụ ấn 1 nút thì 1 hàm chạy độc lập. Ta có thể tùy chỉnh resume,
//stop, exit, start. Ấn start nhiều lần thì phải chờ xong mới thực hiện tiếp. Đó là tiêu chuẩn cơ bản.
//Ta cần chú ý: khi tạo, hàm của ta k đc phụ thuộc vào biến hay hàm của thread khác or có thể dùng thread lock, khi dùng k đc
//phụ thuộc cả vào instance class đó vì chẳng lẽ cứ gọi 1 hàm độc lập thì phải có 1 instance mới đc tạo ra->thế chẳng may
//instance đó bị xóa trc khi cái thread finish thì sao->trừ khi ta xử lý đc vc đó tức là trc khi xóa phải phát signal disconnect
//cho nó dừng trc; khi chạy thì phải đảm bảo nó đc chạy độc lập và duy nhất; khi tắt thì nó bị dừng và xóa.
