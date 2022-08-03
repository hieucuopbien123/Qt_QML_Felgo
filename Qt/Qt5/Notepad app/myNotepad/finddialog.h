#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Finddialog;
}

class Finddialog : public QDialog
{
    Q_OBJECT

public:
    explicit Finddialog(QWidget *parent = nullptr);
    ~Finddialog();

signals:
    void find(QString text);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Finddialog *ui;
};

#endif // FINDDIALOG_H
