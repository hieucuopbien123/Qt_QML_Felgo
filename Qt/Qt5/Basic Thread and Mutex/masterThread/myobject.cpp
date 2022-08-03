#include "myobject.h"

MyObject::MyObject(QObject *parent) : QObject(parent)
{
    thread=new MyThread(QThread::create(std::bind(&MyObject::doWork,this)));
    /*create đối số của nó buộc là std::bind-> hàm bth k đc.
     * Từ trc tới h ta biết rằng: Function&& tức là tham chiếu rvalue và giá trị trả về của hàm cx là rvalue.
     * std::bind trong c++ là hàm trói buộc làm giảm số lượng biến của 1 hàm. VD:auto somu= std::bind(pow,_1,7);->sẽ tạo
     * hàm somu là hàm nhận 1 đối số và trả về mũ 7 nó lên, nó là hàm tạo từ pow và đối số 2 bị fix r.
     * Nhưng trong Qt nó bị khác đi, ta bị ép phải truyền vào create với std::bind, đối số của bind lại là &<tên class>
     * ::<hàm> và biến con trỏ class chứa hàm, các đối số của hàm. trong C++ muốn dùng std::bind phải include <functional>
     */
    this->moveToThread(thread);//tức move cái slot bên dưới vào thread riêng là biến thread

//    QObject::connect(thread,SIGNAL(started()),this,SLOT(doWork()));
//    QObject::connect(this,SIGNAL(workFinished()),thread,SLOT(quit()));

//    QObject::connect(this,SIGNAL(workFinished()),this,SLOT(deleteLater()));
//    QObject::connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));

    thread->start(QThread::HighPriority);
//    thread->wait();
    for(int i=0;i<10000;i++)
    {
        qDebug() << "main " << i;
    }
}

void MyObject::doWork()
{
    for(int i=0;i<10000;i++)
    {
        mutex->lock();
        qDebug() << "doWork :" << i;
        mutex->unlock();
        //mutex khi lock thì các biến giữa lock và unlock sẽ bị khóa và các thread khác cx như các hàm khác k thể truy cập

        //nếu đang định lock biến này mà 1 thread khác đã lock nó r-> chờ biến kia unlock ms đc lock
        //QMutex con trỏ thì khai báo có thể gán mode là recursive hay k, nếu biến bth thì khởi tạo mặc định->NonRecursive
        //QMutexRecursive là 1 class riêng cho dễ thao tác là khởi tạo ra biến QMutex có isRecursive==true mà thôi

        //recursive cho phép ta gọi nhiều hàm lock đệ quy với nhau(lồng nhau) và số hàm unlock phải = số hàm lock->vì có những
        //lúc ta unlock 1 biến này nhưng vẫn muốn khóa biến khác nhiều tâng
        //nonrecursive thì lock và unlock ms lock tiếp-> nếu k sẽ deadlock(là TT CT crash)

        //isRecursive,trylock,try_lock
        //(trylock sẽ lock trong 1 k tg nào đó còn try_lock tương tự máy sẽ quyết định)
    }
    emit workFinished();
}
