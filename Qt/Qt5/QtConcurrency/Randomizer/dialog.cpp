#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
        qDebug() << "Filter: " << QThread::currentThreadId();
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::getNumber(int &baseNumber)
{
    int high = 100;
    int low = 1;
    int random = QRandomGenerator::global()->generate() % ((high +1) - low) + low;
    //trong C++ có srand(<giá trị động>) truyền vào seed và lấy ra bằng rand(). Trong Qt phiên bản cũ cx v.
    //Nếu k rand() nhiều lần 1 Ct sẽ chỉ ra các giá trị như nhau. Bh đã cải tiến thành QRandomGenerator
    //Trong phiên bản qt mới,dùng qrand()luôn mà k có qsrand(time(NULL))->dù sao thì cx nên dùng QRandomGenerator thay cho nó

    qDebug() << "Randomizing " << baseNumber << " = " << random;
    baseNumber = random;

    return 0;//Map nó sẽ thay đổi trực tiếp đầu vào nên phải đúng form là có &. Và ta return cái gì kệ mẹ.
    //Nhưng mapped sẽ lấy giá trị trả về gán làm thành 1 list và sử dụng nên cần return biến sau khi đổi->k có &
}

void Dialog::on_pushButton_clicked()
{
    QList<int> list;

    //Add 0 to 99
    for(int i = 0; i < 100; i++)
    {
        list.append(i);//list k cần khởi tạo kích thước mà nó như vector v, cứ append vào là mở rộng ra
    }

    qDebug() << "Started!";

    //Block until all have completed
    QtConcurrent::blockingMap(list,&Dialog::getNumber);
    //block + truyền tất cả các item trong list vào hàm getNumber và thực hiện lệnh getNumber(item);

    qDebug() << "Finished!";

    ui->listWidget->clear();

    //update the ui
    for(int i = 0; i < list.count(); i++)
    {
        ui->listWidget->addItem(QString::number(i) + " = " + QString::number(list.at(i)));
    }
}
//Cách làm như v thì chả có ứng dụng gì của bất đồng bộ cả, ta nên gọi hàm k bị block là map sau đó
//thực hiện đến hết hàm, khi nào cần dùng giá trị thì QFutureWatcher gọi waitForFinish và lấy kết quả
//với QFuture results=> như v thì trong qtr ta làm vc khác thì hàm vẫn chạy, chỉ khi cần dùng mới cần
//đảm bảo hàm thực hiện xong để lấy giá trị mà thôi => simple

QString Dialog::makeChanges(QString item)
{
    item.append(" Cats");
    return item;//lôi quên return
}

void Dialog::on_pushButton_2_clicked()
{
    qDebug() << "Map: " << QThread::currentThreadId();
    ui->listWidget_2->clear();
    QStringList before;
    before << "Two" << "Three" << "Four";

    QStringList after = QtConcurrent::blockingMapped(before,&Dialog::makeChanges);
    //cái này khác blockingMap vì nó generate 1 chuỗi mới trả về
    //tương tự hàm map và mapped chỉ là nó k block nên có nguy cơ deadlock nếu đang chạy dở thì thay đổi ở thread khác or gọi
    //tiếp hàm này khi nó chưa chạy xong,..->thêm wait là lại giống blockingMap thôi

    ui->listWidget_2->addItems(after);
}

bool Dialog::filter(QString itemBefore)
{
    qDebug() << "Filter: " << QThread::currentThreadId();
    if(itemBefore.toLower() == "like" || itemBefore.toLower() == "hieu") return false;
    return true;
}

void Dialog::reduce(QString &result, const QString item)
{//duyệt qua từng item mà filter là true,xử lý,lưu vào result
    result += item + ",";
}

void Dialog::on_pushButton_3_clicked()
{
    ui->listWidget_3->clear();
    QStringList before;
    before << "Hello" << "World" << "Like" << "Hieu";
    //dùng khi cần lọc cj ra, đương nhiên là trên 1 thread khác trong threadpool r. Nó sẽ block cho đến khi hết ms chạy tiếp
    QStringList after = QtConcurrent::blockingFiltered(before,&Dialog::filter);
    ui->listWidget_3->addItems(after);//k add đc QList trực tiếp nhưng add đc QStringList luôn
    //block thì return QStringList luôn còn k có thì mới QFuture và dùng đc hàm wait
}

void Dialog::on_pushButton_4_clicked()
{
    QStringList nameList;
    nameList << "Hieu" << "Hang" << "Hung" << "like";
    QFuture<QString> reducedName = QtConcurrent::filteredReduced(nameList, &Dialog::filter,
                                                                 &Dialog::reduce,QtConcurrent::UnorderedReduce);
    reducedName.waitForFinished();//hàm blockingFilterdReduced cũng chỉ là gọi thêm hàm này under the hood
    //Các function khi truyền vào hàm nhớ là phải chuẩn type trả ra và từng đối số truyền vào
    //KeepFunctor là bool(QString) còn ReduceFunctor là void(QString&,const QString). UnorderedReduce sẽ arbitrary,..
    //K nhất thiết phải là QString, có thể thay bằng int nhưng phải đúng cấu trúc đó

    QString result = reducedName.result();
    result.chop(1);
    ui->lineEdit->clear();
    ui->lineEdit->setText(result);
    //Tương tự: map,mapped,mappedreduced,filteredReduced,filtered,filter trả ra QFuture;
    //Còn các hàm blocking sẽ block đến khi thực hiện xong. Có ed thì return sequence
}
