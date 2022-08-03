#include "laptop.h"

laptop::laptop(QObject *parent, QString name) : QObject(parent)
{
    this->name = name;
    qInfo() << "My laptop " << "constructed";
}

//laptop k còn là kiểu dữ liệu cơ bản nx nên k có copy constructor(vẫn có move constructor là truyền biến bth vào địa
//chỉ laptop& var)=> implement copyconstructor.
//QObject có marco Q_DISABLE_COPY nên sẽ k thể copy được biến này và các class kế thừa nó cx k copy biến này-> ta chỉ
//implement copy các từng cái bên trong như ý ta chứ k đc với QObject=>vẫn có thể dùng QObject&var để truyền vào k copy
laptop::laptop(laptop &laptop)
{
    this->name = laptop.name;
    this->setObjectName(laptop.objectName());
//    copy từng cái gì thì nói ra
}
//kiểu this chính là biến copy cần copy từ laptop truyền vào=>Tại sao lại dùng & mà k dùng bth khi implement copy bởi vì
//copy chưa có thì làm sao mà dùng luôn đc-> ta dùng bản chất biến để lấy giá trị gán cho biến copy mơi thông qua gán =
//Các class k kế thừa QObject mà tự tạo thì implement copy constructor ta truyền bth (laptop laptop) vì kiểu cơ bản nó có
//rồi và ta reimplement lại mới làm đc như v chứ ở đây chưa có.NN vì marco Q_DISABLE-COPY của QObject ảnh hưởng biên laptop

laptop::~laptop()
{
    qInfo() << name << " destructed";
}

void laptop::test()
{
    qDebug() << "name is " << name;
}


