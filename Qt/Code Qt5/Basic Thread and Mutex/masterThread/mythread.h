#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDebug>

class MyThread : public QThread
{
public:
    MyThread(QThread*thread);
    void run() override
    {
        for(int i=0;i<100;i++)
        {
            this->msleep(10);//chờ 10ms thực hiện tiếp
            qDebug() << "thread class: " << i;

            if ( QThread::currentThread()->isInterruptionRequested() )//điều khiển
            {
                return;
            }
        }
    }
};

#endif // MYTHREAD_H
