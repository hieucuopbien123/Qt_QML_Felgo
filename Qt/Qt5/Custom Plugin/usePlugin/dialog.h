#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPluginLoader>
#include "IPlugin.h"
#include <QDir>

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
    void on_TestPlugin_clicked();

private:
    Ui::Dialog *ui;
    void loadPlugin(const QString&);
};
#endif // DIALOG_H
