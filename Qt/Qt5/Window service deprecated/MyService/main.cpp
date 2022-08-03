#include <QApplication>
#include "myservice.h"

int main(int argc, char *argv[])
{
    MyService service(argc, argv);
    return service.exec();//rule of usage có chỉ ra là k đc dùng QCore trực tiếp
}
