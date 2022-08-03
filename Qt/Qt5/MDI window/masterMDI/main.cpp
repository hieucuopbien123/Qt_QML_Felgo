#include <QApplication>
#include "window.h"

int main(int argc,char*argv[])
{
    QApplication app(argc,argv);
    window screen;
    screen.show();


    return app.exec();
}
