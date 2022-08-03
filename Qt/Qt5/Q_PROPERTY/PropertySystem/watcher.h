#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include "mainwindow.h"
#include <QDebug>

class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = nullptr);

signals:
public slots:
    void priorityChanged(MainWindow::Priority priority);

};

#endif // WATCHER_H
