#include <QCoreApplication>
#include <console.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Console console;
    qDebug() << qApp->thread();

    return a.exec();
}
