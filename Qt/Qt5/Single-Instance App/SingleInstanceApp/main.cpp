#include <QCoreApplication>
#include "singleinstance.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString name = "Local server 1";

    SingleInstance instance;

    if(instance.checkPreviousWindow(name, QCoreApplication::arguments()))//đối số 0 là link tới file exe còn gì
    {
        return 0;
    }
    qDebug() << "This app is only one instance";
    instance.listen(name);

    return a.exec();
}
