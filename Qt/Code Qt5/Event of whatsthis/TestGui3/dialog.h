#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "eventofwhatsthis.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void showLink(const QString &link);
private:
    Ui::Dialog *ui;
    eventOfWhatsThis *event;
};
#endif // DIALOG_H
