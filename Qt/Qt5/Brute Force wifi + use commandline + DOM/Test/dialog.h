#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QtXml>
#include <QNetworkConfigurationManager>
#include <QTcpSocket>
#include <QtConcurrent>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    int run(int index);
    int check();
    char* checkLoop();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    char password[9];
    int isQuit;
};
#endif // DIALOG_H
