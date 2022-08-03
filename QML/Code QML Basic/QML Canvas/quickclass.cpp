#include "quickclass.h"
#include <QDebug>

QuickClass::QuickClass(QObject *parent) : QObject(parent)
{

}

int QuickClass::testQMLClass(int value)
{
    qDebug() << "QML C++ Class Called " << value;
    return value++;
}
