#include <QCoreApplication>
#include <testenum.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestEnum test;
    test.doTest(QString("TEST1"));
    test.doTest("Test");

    return a.exec();
}
