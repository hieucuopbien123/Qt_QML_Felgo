#include "window.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QFontComboBox>
window::window()
{
    //MDI
    QMdiArea * allScreen=new QMdiArea;
    setCentralWidget(allScreen);

    QTextEdit * subScreen1=new QTextEdit;
    QTextEdit * subScreen2=new QTextEdit;

    QMdiSubWindow* subWin1=allScreen->addSubWindow(subScreen1);
    QMdiSubWindow* subWin2=allScreen->addSubWindow(subScreen2);

    //Các thao tác cơ bản với QMainWindow
    QMenu *menu=menuBar()->addMenu("File");
    QAction * thaoTacThoat=new QAction("thoát");
    menu->addAction(thaoTacThoat);

//    thaoTacThoat->setShortcut(QKeySequence("Ctrl+Z"));//các phím tắt phổ biến vị trùng->k dùng đc ctrl+c chẳng hạn
    thaoTacThoat->setShortcut(QKeySequence("Ctrl+Q"));
    thaoTacThoat->setCheckable(true);
    thaoTacThoat->setChecked(true);
    connect(thaoTacThoat,SIGNAL(triggered()),qApp,SLOT(quit()));

    QToolBar *toolbar1=addToolBar("hello");
    QToolBar *toolbar2=addToolBar("hello");
    thaoTacThoat->setIcon(QIcon("img/smiley.png"));
    thaoTacThoat->setIconVisibleInMenu(false);
    toolbar1->addAction(thaoTacThoat);
    toolbar1->addSeparator();
    toolbar1->addWidget(new QFontComboBox());
}
