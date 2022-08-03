#include <QApplication>
#include <server.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    qRegisterMetaType<CommandRequest>();
    //cái qRegisterMetaType sẽ đăng ký cái type thành metatype và từ đó nó dùng đc QMetaProperty
    //để đăng ký như v thì cái class là template kia phải có Q_DECLARE_METATYPE sẵn r.1 cái cho QMetaProperty,1 cho QVariant
    server server;
    server.startServer(1234);

    return a.exec();
}
