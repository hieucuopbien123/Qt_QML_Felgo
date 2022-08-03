#ifndef QMETA_H
#define QMETA_H

#include <QApplication>
#include <QWidget>
#include <QDebug>

class QMeta:public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "NTH")
    Q_CLASSINFO("url", "http://doc.moosesoft.co.uk/1.0/")
     #ifndef Q_MOC_RUN//moc là meta object compiler
     #  define MY_CUSTOM_TAG
     #endif
public:
    QMeta(QObject*object);
    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)
    void setN(int a){n=a;}
signals:
    void test();
public slots:
    MY_CUSTOM_TAG void testSlot(){qDebug() << "This is a slot";}
    int testSlot2(int a){qDebug() << "100000 " << a;}
private:
    int n;
};

#endif // QMETA_H
