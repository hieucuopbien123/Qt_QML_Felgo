#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void showTime();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
};
#endif // MAINWINDOW_H
