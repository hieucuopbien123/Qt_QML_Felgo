#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::doTask(int &number)
{
    qDebug() << "Starting " << number;
    int max = 10;
    for(int i = 0; i < max; i++)
    {
        QThread::currentThread()->msleep(50);
        qDebug() << "Processing " << number << " " << i << " of " << max;
    }

    qDebug() << "Stopped " << number;
}


void Dialog::on_pushButton_clicked()
{
   QVector<int> vector;
   for(int i = 0; i < ui->spinBox->value(); i++)
   {
       vector.append(i);
   }

   QProgressDialog pDialog;//cửa sổ chuyên hiển thị vc chạy thanh progressbar. Mặc định nó có 1 thanh progressBar và 1 nút
   //cancel. Ấn cancel thì cái dialog biến mất. Ta tùy ý chỉnh mọi thứ trong nó. Tắt dialog và ấn cancel đều phát signal cancel
   pDialog.setLabelText("Processing");

   QFutureWatcher<void> watcher;//QFutureWatcher cx chỉ giống QFuture nhưng thao tác đc vs signal slot
   //Dùng QFuture như bth->tạo QFutureWatcher setFuture cái biến QFuture đó->thao tác với signal slot xử lý tiến trình
   //Tức là nó k điều khiển đc hành động làm gì và tiến trình chạy đến đâu.Ta chỉ có thể thao tác với kết quả or run/cancel

   connect(&pDialog,SIGNAL(canceled()),&watcher,SLOT(cancel()));//ấn cancel thì làm gì
   connect(&watcher,SIGNAL(finished()),&pDialog,SLOT(reset()));
   //reset progressBar và hidden dialog nếu autoClose là true(mặc định),setRange của progressBar kp là set % mà là set giá trị
   //để nó chạy %.VD ta setRange(0,5)thì 5 là 100%.Rồi reset()thì nó lại quay về 0,0.Nhờ v ta ms set lt đc khi đổi gt spinbox
   connect(&watcher,SIGNAL(progressRangeChanged(int,int)),&pDialog,SLOT(setRange(int,int)));
   connect(&watcher,SIGNAL(progressValueChanged(int)),&pDialog,SLOT(setValue(int)));

   watcher.setFuture(QtConcurrent::map(vector,&Dialog::doTask));
   //Chú ý các hàm map, filter điều khiển đc tiến trình nhưng hàm run k điều khiển đc. Ta có thể dừng hàm run =Đk như ở project đầu
   //khi ta thực hiện map với 1 sequence thì cái số lượng ptử trong danh sách chính là cái progressValue của qtr QFutureWatcher
   //ví dụ nó có 10 phần tử thì progressRange từ 0-9 còn progressValue là số lượng phần tử đã xử lý xong.
   //Range đang là 0,0->chạy cái này phát ra progressRangeChanged,progressValueChanged luôn
   pDialog.exec();//chỉ cửa sổ hiện thị cái main thread bị ngừng chứ các tiến trình khác vẫn chạy bth
   watcher.waitForFinished();//or QFuture gọi từ đầu blockingMap

   if(watcher.isCanceled())
   {
       qDebug() << "Canceled!!";
       QMessageBox::critical(this,"Canceled","You clicked cancel!");
   }
   else{
       qDebug() << "Finished!!";
       QMessageBox::information(this,"Finished","All done!");
   }
   //cái watcher và pdialog k cần là con trỏ vì hàm này thực hiện xong là 2 biến đó k dùng nx r. Ấn là tạo, xong là xóa
}
