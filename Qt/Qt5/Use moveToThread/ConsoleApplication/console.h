#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QThread>
#include <QTextStream>
#include <QCoreApplication>

//dường như class nào cx ít nhất là kế thừa QObject. Vì đều dùng signal,slot,.. trừ những class lưu toàn data mà k thao tác j
class Console : public QObject
{
    Q_OBJECT
public:
    explicit Console(QObject *parent = nullptr);

public slots:
    void getText();
    void printText(QString);

signals:
    void textAvailable(QString);

private:
    QThread myThread;

};

#endif // CONSOLE_H
