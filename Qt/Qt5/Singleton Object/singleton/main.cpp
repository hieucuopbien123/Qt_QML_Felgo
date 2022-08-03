#include <QCoreApplication>
#include "test.h"
#include "consumer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Consumer cConsumer;

    //From the object
    //Tester::Instance()->doSomething();

    //No object
    test::doSomething();
    //bên trong doSomething phát 1 signal instance mà ta k hề tạo ra 1 biến instance của test

    return a.exec();
}
