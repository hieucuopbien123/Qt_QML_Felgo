#include <QtTest>
#include <QObject>

class TestString : public QObject
{
    Q_OBJECT

public:
    TestString();
    ~TestString();

private slots:
    void test_case1();

};

TestString::TestString()
{

}

TestString::~TestString()
{

}

void TestString::test_case1()
{

}

QTEST_APPLESS_MAIN(TestString)

#include "tst_teststring.moc"
