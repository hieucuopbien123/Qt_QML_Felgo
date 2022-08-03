#include "myplugin.h"

MyPlugin::MyPlugin(QObject *parent) : QObject(parent)
{

}

void MyPlugin::functOfPlugin(const QString& mess) const// chú ý có const ở sau hàm thì ở đâu cx phải có
{
    QMessageBox::information(new QWidget(),"Title",mess);
}
