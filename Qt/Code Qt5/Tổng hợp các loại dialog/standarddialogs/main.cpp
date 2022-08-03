#include <QApplication>
#include <QStyleHints>
#include <QDesktopWidget>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QDebug>

#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(Dialog::tr("Standard Dialogs"));//cx set name cho cửa sổ ở đay đc

#ifndef QT_NO_TRANSLATION//QT_NO_TEXTCODEC-> các marco này thực chất là do ta tự defined ra, tức là nếu ta chưa làm thế này ở
    //đâu đó khác thì sẽ thực hiện nó trong đây. Nó khác với QT_PRINTSUPPORT_LIB và QT_CONFIG clipboard là các cái đã có
    //trong máy thg có cái đó, thì ở đây QT_NO_TRANSLATION là 1 cái tên lạ, mục đích là để đánh dấu tên khai báo cái translation
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        app.installTranslator(translator);
    qDebug() << QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    //hàm QLibraryInfo lưu thông tin về các thư viện of Qt-> k có ứng dụng trong thực tế các app ta tạo

    //hàm location sẽ trả về thư mục chứa file translation của qt->ý là translator sẽ load cái file tên QLocale::system().name()
    //tìm trong cái thư mục đó, hàm load tự thêm đuôi file là qm nếu k specific cho nó
    //cụ thể ở đây: nó sẽ load C:/Qt/5.15.2/mingw81_64/translations/qt_en_US.qm nhưng nó có tồn tại đâu nhỉ
#endif

    Dialog dialog;
    if (!QGuiApplication::styleHints()->showIsFullScreen() && !QGuiApplication::styleHints()->showIsMaximized())
    {//QStyleHints là class lưu các thể loại thao tác, ví dụ nếu ta double click, giữ chuột ở trong cửa sổ bao lâu thì
        //class này sẽ kiểm soát, là mode gì full màn hình hay k chẳng hạn, gọi đến nó từ QGuiApplication
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(&dialog);
        //hàm desktop() trả ra QDesktopWidget quản lý màn hình desktop như số lượng cửa sổ, và geometry
        dialog.resize(availableGeometry.width() / 3, availableGeometry.height() * 2 / 3);
        //resize là kích thước, move là vị trí. setGeometry là tất
        dialog.move((availableGeometry.width() - dialog.width()) / 2,
                    (availableGeometry.height() - dialog.height()) / 2);
    }
    dialog.show();

    return app.exec();
}
