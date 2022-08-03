#include "consumer.h"

Consumer::Consumer(QObject *parent) :
    QObject(parent)
{
    connect(Tester::Instance(),SIGNAL(testSignal()), this,SLOT(testSlot()));
    //Ta tưởng tượng có thêm 1 biến global của 1 class bất kỳ truy xuất bất cứ lúc nào với Instance()
}

void Consumer::testSlot()
{
    qDebug() << "It's working!!!!";
}
