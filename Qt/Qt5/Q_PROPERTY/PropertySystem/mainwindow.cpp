#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::newMethod()
{
    qDebug("hello");
    this->setProperty("priority","VeryLow");
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::Priority MainWindow::priority() const
{
    return m_priority;
}

void MainWindow::setPriority(const Priority &priority)
{
    m_priority = priority;
    emit(priorityChanged(priority));
}

