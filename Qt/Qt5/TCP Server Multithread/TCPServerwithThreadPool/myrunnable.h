#ifndef MYRUNNABLE_H
#define MYRUNNABLE_H

#include <QRunnable>
#include <QObject>
#include <QTcpSocket>

class myRunnable : public QObject,public QRunnable
        //thứ tự kết thừa cx qtr, ta đặt là cái nào lên trc là chủ yếu kế thừa cái đó
{
    Q_OBJECT
public:
    myRunnable();
    int socketDescriptor;
    //QRunnable là 1 class trừu tượng->ta muốn dùng buộc phải dùng các class kế thừa nó or ta tự tạo class kế thừa để dùng
    //class trừu tượng nhưng kp interface nhé
    void run();//buộc tạo run để chạy
public slots:
    void readyRead();
    void disconnected();
private:
    QTcpSocket *socket;
};



#endif // MYRUNNABLE_H
