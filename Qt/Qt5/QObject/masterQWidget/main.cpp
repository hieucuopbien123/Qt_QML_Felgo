#include <QApplication>
#include <QtWidgets>
#include "testobject.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //QObject thao tác với quá trình code(signal,slot,lớp kế thừa,sự kiện)(cũng giống QMetaObject)
    QLabel *label = new QLabel;
    QLineEdit *lineEdit = new QLineEdit;
    QObject::connect(lineEdit, &QLineEdit::textChanged,
                     label,  &QLabel::setText);//nếu k dùng SIGNAL,SLOT=> có &<tên class><chỉ thị tiền xử lí ::>

    QObject::connect(lineEdit, &QLineEdit::textChanged,[&](){label->setText(QString("Hello"));});//nhớ hàm trong lamba phải có ";"
    //dùng vs cả function bth cứ truyền vào
    QObject::disconnect(lineEdit, nullptr, nullptr, nullptr);
    //cx TT như lineEdit->disconnect(); chỉ khác là k còn là hàm static nx // muốn disconnect cái gì thì gán null cái đó
    lineEdit->disconnect(SIGNAL(mySignal()));//cx TT như QObject::disconnect(lineEdit, SIGNAL(mySignal()), nullptr, nullptr);
    //giả sử có 1 signal mySignal ở đây
    QObject::disconnect(lineEdit, nullptr, label, nullptr);//= lineEdit->disconnect(label);

    QWidget* parentWidget=new QWidget;
    QPushButton * button1=new QPushButton(QObject::tr("Hello %n","test tr() thôi",10));
    button1->setObjectName("button1");
    //với ui thì tự động đặt objectName=tên biến còn nếu tạo bth thì nó objectName là rỗng(nó kp tên biến)

    QPushButton * testFindChild = parentWidget->findChild<QPushButton *>("button1");
    QPushButton *button = parentWidget->findChild<QPushButton *>("button1", Qt::FindDirectChildrenOnly);
    //2 đối số 1 là tên 2 là mode mặc định là recursive.chỉ tìm chính lớp cha đó, k tìm sâu hơn với FindDirectChildrenOnly
    QList<QPushButton *> allPButtons = parentWidget->findChildren<QPushButton*>();
    QList<QPushButton *> childButtons = parentWidget->findChildren<QPushButton *>(QString(), Qt::FindDirectChildrenOnly);
    //muốn lấy đối số 2 buộc truyền đối số 1=> ta tìm tất cả thì để QSring()

    // QVBoxLayout inherits QObject and QLayoutItem
    QVBoxLayout *layout = new QVBoxLayout;//ta chỉ dùng khi nó kế thừa từ QObject
    layout->inherits("QObject");        // returns true
    layout->inherits("QLayoutItem");    // returns true (even though QLayoutItem is not a QObject)
    //kiểm chứng tính inherits(khá vô dụng)->k vô dụng đâu

    MyWidget*testEventFilter=new MyWidget;
    QPushButton* buttonTestFilter=new QPushButton;
    buttonTestFilter->installEventFilter(testEventFilter);
    //cái eventFilter nó xử lí event có đk là 1 QObject. Ta dùng installEventFilter để cài nó cho biến QObject khác và biến đó sẽ xử lí
    //đk như trong hàm eventFilter kia. tức là nó bắt mọi event send cho nó và tự động thực hiện với filter là chính nó(biến object ms
    //đc install vô)=>các hàm event đó sẽ tự thực hiện khi dùng buttonTestFilter mà đụng event

    QObject *obj = new QPushButton;
    obj->metaObject()->className();             // returns "QPushButton"->như v là dùng đc mọi hàm của QMetaObject r

    QPushButton::staticMetaObject.className();  // returns "QPushButton"
//pb khi có con trỏ trỏ vào 1 đối tượng nào đó mà thừa kế từ QObject thì ta dùng metaObject, nếu k có thì dùng staticMetaObject. metaObject
//là biến trả về thông tin về class, tên,signal slot của class kế thừa từ QObject(khá vô dụng)
    //metaobject là siêu dữ liệu cung cấp thông tin thêm về 1 cj đó

    obj->moveToThread(QApplication::instance()->thread());
    //instance() của QCoreApplication sẽ return con trỏ trỏ đén cái app hiện tại. thread của QObject trỏ vào cái thread mà cái object đó
    //nằm trong.Movetothread sẽ move object to thread truyền vào. Ở đây nó move cái obj vào cái mainthread do thread của app hiện tại
    //tức là nhét cái obj vào cái thread thực thi qApp hien tại

    QObject *objTimer = new QTimer;          // QTimer inherits QObject
    QTimer *timer = qobject_cast<QTimer *>(objTimer);
    // timer == (QObject *)obj
    QAbstractButton *buttonTestTimer = qobject_cast<QAbstractButton *>(objTimer);
    // buttonTestTimer == nullptr vì k bắt từ đúng nguồn
    //blockSignals,children,dumpObjectInfo,isWidgetType,isWindowType,killTimer,parent,dynamicPropertyNames,setProperty,
    //removeEventFilter,setParent,signalsBlocked,startTimer,objectNameChanged,sender,typedef QObjectList,
    //(senderSignalIndex),property,((dis)connectNotify),dumpObjectTree
    //(dumpObjectInfo in ra thông tin signal/slot của biến đó ở console,dumpObjectTree là in ra tất cả con của nó luôn)
    //(senderSignalIndex in ra index của signal, cái này mỗi metaObject của nó đều có index để lưu và hàm này giúp lấy
    //ra, hàm này chỉ gọi đc trong slot kích hoạt bởi signal-> mỗi signal như nhau có đối số khác nhau thì có index khác)
    //((dis)connnectNotify tự thực hiện khi QObject nào đc connect vs signal->nó thực hiện cj thì ta k cần bt)
    //hàm protected chỉ dùng đc trong hàm của class đó

    return app.exec();
}
