#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QTreeWidgetItem>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QInputDialog>
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_addingButton_clicked();
    void on_addingMultButton_clicked();
    void on_studentManagementEdit_itemActivated(QTreeWidgetItem *item, int column);
    void on_removingButton_clicked();

private:
    Ui::Widget *ui;
    QVector<student*> studentList;
    int num;
};
#endif // WIDGET_H
