#include <QCoreApplication>
#include "libdll.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Libdll testDll;
    testDll.Test();

    return a.exec();
}
