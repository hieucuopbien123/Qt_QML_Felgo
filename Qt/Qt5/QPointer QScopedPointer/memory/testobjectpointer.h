#ifndef TESTOBJECTPOINTER_H
#define TESTOBJECTPOINTER_H

#include <QObject>

class TestObjectPointer : public QObject
{
    Q_OBJECT
public:
    explicit TestObjectPointer(QObject *parent = nullptr);

signals:
    void printHello();
};

#endif // TESTOBJECTPOINTER_H
