#ifndef QUICKCLASS_H
#define QUICKCLASS_H

#include <QObject>

class QuickClass : public QObject
{
    Q_OBJECT
public:
    explicit QuickClass(QObject *parent = nullptr);
    Q_INVOKABLE int testQMLClass(int value);

signals:

};

#endif // QUICKCLASS_H
