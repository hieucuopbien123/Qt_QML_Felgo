#include "watcher.h"

Watcher::Watcher(QObject *parent) : QObject(parent)
{

}

void Watcher::priorityChanged(MainWindow::Priority priority)
{
    qInfo() << "priority: " << priority;
}
