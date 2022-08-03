#ifndef LAPTOP_H
#define LAPTOP_H

#include <QObject>
#include <QDebug>

class laptop : public QObject
{
    Q_OBJECT
public:
    //biến name được khai báo sau parent thì buộc phải có giá trị mặc định cho nó
    explicit laptop(QObject *parent = nullptr, QString name = "");
    laptop(laptop& laptop);
    ~laptop();

    QString name;
    void test();

signals:

};

#endif // LAPTOP_H
