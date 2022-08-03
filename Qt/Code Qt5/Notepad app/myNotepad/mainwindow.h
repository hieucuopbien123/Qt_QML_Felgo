#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QColorDialog>
#include <QColor>
#include <QFontDialog>
#include <QFont>
#include <QPrinter>
#include <QPrintDialog>
#include <QDesktopServices>
#include <QTextCodec>
#include <QSettings>
#include "finddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void load(QString);

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionClose_triggered();
    void on_actioncopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionAbout_App_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionColor_triggered();
    void on_actionHighlight_triggered();
    void on_actionFont_triggered();
    void on_actionMode_triggered();
    void on_actionPrint_triggered();

    void on_actionFind_triggered();
    void find(QString text);

private:
    Ui::MainWindow *ui;
    bool isOpen;
    QString current_path;
    bool mode;
    QFile file;
    void readFile();
    QColor colorTextFix;
    void loadPosition();
    void savePosition();
    Finddialog* findDialog;
};
#endif // MAINWINDOW_H
