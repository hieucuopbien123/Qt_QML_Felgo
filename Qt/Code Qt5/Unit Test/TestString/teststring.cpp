#include "teststring.h"

TestQString::TestQString()
{

}

void TestQString::toUpper()
{
    //    QString str = "Hello";
    //    QVERIFY(str.toUpper() == "HELLO");
    QFETCH(QString, string);
    QFETCH(QString, result);

    QCOMPARE(string.toUpper(), result);
}

void TestQString::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";//trả về kiểu QTestData
    QTest::newRow("mixed")     << "Hello" << "HELLo";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

//QTEST_MAIN(TestQString)
