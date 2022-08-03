#include <QCoreApplication>
#include "libstatic.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Libstatic testStatic;
    testStatic.test();

    return a.exec();
}
