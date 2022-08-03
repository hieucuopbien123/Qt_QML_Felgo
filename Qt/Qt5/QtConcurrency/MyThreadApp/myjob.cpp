#include "myjob.h"

MyJob::MyJob(QObject *parent) : QObject(parent)
{
    mStop = false;
}

MyJob::~MyJob()
{
    qDebug() << "Delete job";
}

void MyJob::start(QString name)
{
    mStop = false;
    for(int i = 0; i < 99999; i++)
    {
        if(mStop) return;
        qDebug() << "From thread " << i << " " << QThread::currentThreadId();
        emit onNumber(name,i);
        QThread::currentThread()->msleep(100);//làm cho cái thread này chậm lại. sleep thì là giây
    }
}

void MyJob::stop()
{
    mStop = true;
}
