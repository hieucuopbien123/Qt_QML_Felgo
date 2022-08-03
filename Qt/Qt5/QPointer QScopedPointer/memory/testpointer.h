#ifndef TESTPOINTER_H
#define TESTPOINTER_H

#include <QObject>
#include <QPointer>
#include "testobjectpointer.h"

class TestPointer : public QObject
{
    Q_OBJECT
public:
    explicit TestPointer(QObject *parent = nullptr);

signals:
    void test();
public slots:
    void printHello();
};

#endif // TESTPOINTER_H
