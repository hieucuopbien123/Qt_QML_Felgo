#include "myservice.h"
#include <QMessageBox>

MyService::MyService(int argc, char **argv) : QtService<QApplication>(argc,argv,"MyService")//3 là tên service
{
    try
    {
        //Set the service information
        setServiceDescription("This is my service.");
        setServiceFlags(QtServiceBase::CanBeSuspended);//có thể suspend đc
    }
    catch(...)
    {
        qCritical() << "An unknown error in the constructor";
    }
}
//thật ra vc sử dụng vô cùng ez, tất cả cái qtservice này chỉ đơn giản là cho ta 1 cái biến khác thay thế cho biến
//QCoreApplication. Khi biến này gọi exec thì chương trình có thể chạy như 1 service, còn QCoreApplication exec thì
//Ct chỉ chạy như 1 Ct bth có debug(k chạy ngầm đc). Và ta có thể thao tác sâu hơn khi chạy ví dụ in ra đường dẫn
//file hay làm gì. Còn lại ta hoàn toàn tạo đc các class khác như 1 Ct bth(nhắc lại: chỉ thay mỗi exec QCore).

//Để sử dụng ví dụ muốn chạy 1 chức năng gì đó ngầm, ta phải reimplement 5 hàm trống là start, pause, resume, stop,
//processCommand. 5 slot này đc thực hiện tự động.
MyService::~MyService()
{
    try
    {
        //TO DO - release any memory
    }
    catch(...)
    {
        qCritical() << "An unknown error in the deconstructor";
    }
}

//thật ra service có 1 class là QServiceController là 1 class chuyên quản lý các service. Vd ta tạo service và install nó
//thì dùng 1 Ct với biến QServiceController ta có thể diều khiển service đó start, stop, resume, thực hiện lênh j,..
//Vd: nó cung 2 hàm start và start(QStringList) ý là chạy service đó có or k có args. Trong example có 1 controller mẫu

//chạy service. Ta muốn khi chạy thì làm gì thì nhét vô. Chỉ dùng khi contructor éo specific args
void MyService::start()
{
    try
    {
        QCoreApplication *app = application();//application lấy con trỏ QCoreApplication
        qDebug() << "Service started!";
        qDebug() << app->applicationDirPath();//hàm của QCoreApplication sẽ trả về thư mục chưa exe
        qDebug() << "Service name: " << this->serviceName();
        //MyClass.dosomething();
    }
    catch(...)
    {
        qCritical() << "An unknown error in the start";
    }
}

void MyService::pause()
{
    try
    {
        qDebug() << "Service paused!";
    }
    catch(...)
    {
        qCritical() << "An unknown error in the pause";
    }
}

//resume sau khi pause. VD ta muốn khi resume nó chạy thêm cj chẳng hạn
void MyService::resume()
{
    try
    {
        qDebug() << "Service resumed!";
    }
    catch(...)
    {
        qCritical() << "An unknown error in the resume";
    }
}

//perform clean up trc khi tắt
void MyService::stop()
{
    try
    {
        qDebug() << "Service stopped!";
    }
    catch(...)
    {
        qCritical() << "An unknown error in the stop";
    }
}

//khi QtServiceController::sendCommand(int code) đc gọi thì cái service đang chạy sẽ thực hiện cái command theo code
//tương ứng
void MyService::processCommand(int code)
{
    try {
        qDebug() << "Process Command";
    }  catch (...) {

    }
}
