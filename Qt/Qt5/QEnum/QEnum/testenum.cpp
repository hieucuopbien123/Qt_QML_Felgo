#include "testenum.h"
#include <QDebug>

void TestEnum::doTest(QString command)
{//cách dùng enum chuyển đổi số và chữ
    QMetaObject metaObject = this->staticMetaObject;//lấy cái chứa enum, từ đó lấy index of mọi thứ method, enum,..
    //staticMetaObject chứ kp staticQtMetaObject
//    QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("TESTENUM"));//lấy cái enum
    QMetaEnum metaEnum = QMetaEnum::fromType<TestEnum::TESTENUM>();//phiên bản mới, cũ ta mới thao tác với index

    switch(metaEnum.keysToValue(command.toUpper().toLatin1()))//keysToValue và valueToKeys là cách đổi
    {
        case TEST1:
            qDebug() << "do sth for test 1";
            break;
        case TEST2:
            qDebug() << "do sth for test 2";
            break;
        case TEST3:
            qDebug() << "do sth for test 3";
            break;
        default:
            qDebug() << "Unknown command!";
            break;
    }
}
