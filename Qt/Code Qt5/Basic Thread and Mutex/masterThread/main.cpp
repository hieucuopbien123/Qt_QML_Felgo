#include <QCoreApplication>
#include "myobject.h"
#include "mythread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyObject *object=new MyObject;

    return a.exec();
}
