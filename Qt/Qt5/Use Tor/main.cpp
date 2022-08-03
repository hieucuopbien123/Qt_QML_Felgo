#include <QCoreApplication>

#include "tortest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TorTest t;
    t.getUrl();

    return a.exec();
}
