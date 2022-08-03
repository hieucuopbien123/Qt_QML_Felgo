#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QDebug>
#include "mythread.h"
#include <QMutex>

class MyObject : public QObject
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);
public slots:
    void doWork();
signals:
    void workFinished();
private:
    MyThread *thread;
    QMutex *mutex=new QMutex(QMutex::NonRecursive);
};

//Cơ chế tạo ra 1 app bằng qt: Nó cần 1 hàm main, và 1 file h,cpp là cửa sổ lớn hiển thị tất cả mọi thứ. Các thuộc tính của
//class đó có thể là các biến class có sẵn trong qt, hoặc là biến khác do ta tạo ra, ta sẽ tạo ra các cặp file h và cpp khác
//kế thừa các lớp có sẵn trong qt và chỉnh sửa thêm các thuộc tính và hàm ta mong muốn, or 1 class mới hoàn toàn cx ok.

//cơ chế: dùng hàm start của QThread sẽ tự động phát signal chạy slot run() là hàm thực hiện độc lập, k ở trong queue chờ.

//Có 2 cách sử dụng QThread và cả hai cách đều phải tuân thủ cái quy định ở trên. Ta có file myobject chính là cửa sổ chính
//hiện ra mọi thứ. Để dùng thread thì ta phải khai báo 1 biến QThread ở trong đó. Sau đó muốn làm gì ở đâu thì ta start ở đó.
//Ngay lập tức hàm run sẽ chạy ngay lập tức, ta chỉ tạo myThread kế thừa và override hàm run làm gì theo ý ta là ok.

//Nhưng thực tế k đơn giản như v, dùng run thì k nhận đối số. Thế bh ta muốn một hàm nào đó của class khác chạy độc lập thì sao
//hàm đó sẽ dùng đối số bất kỳ theo ý ta nhưng chạy độc lập thì cách 1 k làm đc. Đó chính là NN của hàm QObject::moveToThread
//(QThread*), hàm này đc gọi trc khi khai báo signal slot và sử dụng đúng cấu trúc 4 hàm connect thực hiện và xóa thì sẽ khiến
//cho slot của class đc thực hiện độc lập. Xong ta muốn chỗ nào thực hiện thì start ở đó là ok(buộc đủ 4 hàm connect thì sẽ
//xóa đủ biến và CT k bị crash). hàm run() cx đc chạy đồng thời nhưng chậm hơn 1 chút, do đó nên để hàm run trống k=> như v,
//thread đưa ra lời khuyên rằng các slot(hàm cx đc vì biến nó thành slot là xong) của class nên có 1 QThread đi cùng để thực
//hiện đc tối ưu tốc độ-> nv, ta có thể thực hiện mọi hàm thành thread độc lập đc r.

//ở phiên bản mới nó đã cải tiến 4 hàm connect thành hàm create cho phép ta áp dụng với mọi hàm kể cả kp slots

//exit,isFinished,isRunning,loopLevel,priority,requestInterruption,setPriority,terminate,currentThread,sleep,usleep,stackSize,
//setStackSize,idealThreadCount,setTerminationEnabled,exec,quit
//Thật ra thread có thể dùng chạy event loop bên trong(QObject) nên còn có hàm setEventDispatcher, eventDispatcher
//(requestInterruption k kết thúc thread và event chạy trong mà yêu cầu vc này, tùy vào thread mà máy tự xử lý phù hợp)
//(setStackSize là max size of bộ nhớ stack mà ta sử dụng trong thread->ít dùng),(quit sẽ kết thúc eventloop của thread và
//return code 0=QThread::exit(0)/còn terminate sẽ dừng cả thread=>nguy hiểm vì có thể stop ngay mà chưa unlock mutex,..)

#endif // MYOBJECT_H
