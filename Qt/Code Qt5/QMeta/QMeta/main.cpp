#include <QApplication>
#include <QtWidgets>
#include "qmeta.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QMetaObject
    QMeta* object=new QMeta(nullptr);
    //QMetaObject là 1 struct lưu các meta-data của Object đó(meta-data: siêu dữ liệu cx chỉ là cung cấp thêm thông tin).
    //Mỗi khi 1 QObject đc tạo ra thì tự động có 1 QMetaObject tạo ra và gán cho nó, truy cập bằng QObject::metaObject();
    //nó trả về kiểu const QMetaObject* k thể đổi mà Gt mà chỉ cung thông tin. Chúng lưu dưới dạng string->bị hạn chế

    qDebug() << object->metaObject()->classInfo(0).name();
    qDebug() << object->metaObject()->classInfo(1).value();
    //classInfo()của QMetaObject lại trả về QMetaClassInfo là kiểu lưu classInfo tạo bởi Q_CLASSINFO(phải có Q_OBJECT)
    qDebug() << object->metaObject()->classInfoCount();
    qDebug() << object->metaObject()->classInfoOffset();
    //offset đc gọi là phần bù để xác định vị trí của ô nhớ bất kỳ tính từ đầu đoạn(đầu ô nhớ).Ở đây là off set của class
    //Ta tạo nhiều lớp chồng nhau(superclasses) thì hàm này sẽ trả về tổng số lượng các infomation items(Ví dụ số lượng
    //class info) trong các lớp chồng
    qDebug() << object->metaObject()->className();

    //QMetaObject sẽ lưu thông tin đối tượng còn QMetaMethod sẽ lưu các chức năng như hàm, signal,slot của đối tượng.
    //Mỗi chức năng hàm đc lưu gọi là 1 QMetaMethod. Hàm constructor trả về QMetaMethod với index
    qDebug() << object->metaObject()->enumerator(0).name();
    //là enum của class, enumerator trả về QMetaEnum lưu thông tin enum trong class
    qDebug() << object->metaObject()->enumeratorCount();
    qDebug() << object->metaObject()->enumeratorOffset();

    const QMetaObject* metaObject=object->metaObject();

    qDebug() << metaObject->indexOfClassInfo("author");
    qDebug() << metaObject->indexOfEnumerator("Priority");
    qDebug() << metaObject->indexOfMethod("setN") << "fasfasdf";//k tính các method ta tự định nghĩa
    qDebug() << metaObject->indexOfProperty("Priority");//chưa có
    qDebug() << metaObject->indexOfSignal("test");
    qDebug() << metaObject->indexOfSlot("testSlot");//tự định nghĩa k tính
    qDebug() << metaObject->inherits(QObject().metaObject());

    qDebug() << metaObject->method(0).name() << "fsdjfsdjfkodsjf";
    qDebug() << metaObject->methodCount();
    qDebug() << metaObject->property(0).name();
    //trả về QMetaProperty
    qDebug() << metaObject->propertyCount();
    qDebug() << metaObject->propertyOffset();
    qDebug() << metaObject->superClass()->className();
    qDebug() << metaObject->userProperty().name();//trả về property có USER FLAG là true(tự phải set)

    qDebug() << metaObject->checkConnectArgs("test","testSlot");//kiểm tra connect=>static
    metaObject->connectSlotsByName(object);
    //hàm này sẽ tự động tìm tất cả các lớp con của đối số object và kết nối signal của chúng với slot của đối số
    //object theo form: void on_<tên object con>_clicked(tham số)

    QMetaObject::invokeMethod(object, &QMeta::testSlot);//dùng & địa chỉ hàm với hàm k có đối số
    //hàm static invoke method sẽ gọi đến hàm nào đó. Lệnh này giúp hàm đc thực hiện 1 cách an toàn. Khi 2 thread cùng
    //truy xuất đến 1 tài nguyên thì gọi invoke sẽ giúp tài nguyên chỉ bị truy cập bởi 1 thread. Thực hiện thread luôn

    //có đối số thì dùng const char*
    int b;
    QMetaObject::invokeMethod(object, "compute", Qt::DirectConnection,
                              Q_RETURN_ARG(int, b),//GT trả về lưu vào đâu
                              Q_ARG(int, 10));
    //invoke nhanh hay chậm là do ConnectionType: Direct thì ngay lập tức,Queued thì vào main là invoke,Auto invoke đồng
    //bộ nếu obj sống trong cùng thread với lời gọi hàm, còn ngc lại k đồng bộ(tức ta gọi hàm khi mà object exist)
    //Q_RETURN_ARG là marco lưu GT trả về của hàm
    //Q_ARG là marco đối số truyền vào

    QByteArray normType = QMetaObject::normalizedType(" int    const  *");
    // normType is now "const int*"
    //normalizedSignature(const char*method) sẽ đơn giản hóa 1 method bằng cách:loại bỏ spaces,chuyển const lên đầu,
    //loại bỏ đối số của hàm là hso(lấy hs chứ k tự truyền) và lấy bằng GT hs đó luôn

    //QMetaProperty/QMetaEnum/QGenericArgument/QGenericReturnArgument tương tự lưu thông tin quá ez
    //QMetaMethod
    QMetaMethod destroyedSignal = QMetaMethod::fromSignal(&QObject::destroyed);
    qDebug() << destroyedSignal.methodIndex();
    //K tính các signal ta tự tạo,các signal bth của class trong thư viện đã đc gán index sẵn r
    //xong ss signal==deystroySignal nếu muốn ss điều kiện trùng signal

    QPushButton* pushButton=new QPushButton();
    int methodIndex = pushButton->metaObject()->indexOfMethod("animateClick()");
    QMetaMethod method = metaObject->method(methodIndex);//lấy đc 1 hàm bất kỳ của QMetaObject thành QMetaMethod của nó
    method.invoke(pushButton, Qt::QueuedConnection);//lưu method bky r invoke o object nào
    //đó là cách lấy index và phát ra 1 signal lúc nào ta muốn(k đồng bộ). Chú ý pb hàm invoke của QMetaObject và QMetaMethod

    qDebug() << metaObject->method(metaObject->indexOfMethod("testSlot()")).tag();
    //trả về tag mà ta gắn cho hàm nhờ marco Q_MOC_RUN
    //access,isValid,methodSignature,methodType,parameterCount,parameterNames,parameterType
    //parameterTypes,returnType,revision,typeName,Q_METAMETHOD_INVOKE_MAX_ARGS
    //(Còn có QMetaType lưu các type của meta-object)
    //(isValid kiểm tra xó xem đc và invoke đc k)/(methodSignature trả về signature VD setV(double))

    //QMetaType lấy type của biến gì đó
    int id = QMetaType::type("QMeta");//nó trả về GT Enum lưu đủ loại type, lấy id của biến bất kỳ
    if (id != QMetaType::UnknownType) {//nếu unknownType thì k là kiểu dữ liệu CB r// ss, kiểm tra kiểu dữ liệu các biến
        void *myClassPtr = QMetaType::create(id);//tạo biến kiểu bất kỳ
        QMetaType::destroy(id, myClassPtr);//tạo biến có kiểu là id và xóa nó đi
        myClassPtr = 0;
    }
    id = qMetaTypeId<QString>();    // id is now QMetaType::QString//lấy id của kiểu dữ liệu bất kỳ
    //nch class này cung cấp việc lấy dữ liệu kiểu biến=>KT 2 biến cùng kiểu hay k,kiểm tra biến là kiểu CB,tạo,xóa biến


    return a.exec();
}
