#ifndef TESTENUM_H
#define TESTENUM_H

#include <QObject>
#include <QMetaEnum>

class TestEnum: public QObject
{
    Q_OBJECT

public:
    TestEnum() {}
    enum TESTENUM
    {
        TEST1,
        TEST2,
        TEST3
    };
    Q_ENUM(TESTENUM)
    //obsolete la Q_ENUMS(<tên>) đặt ở bcu đâu cx đc, còn Q_ENUM phải khai báo sau enum
public slots:
    void doTest(QString command);

};

#endif // TESTENUM_H
