#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    findDialog = new Finddialog();
    this->setCentralWidget(ui->textEdit);
    isOpen=false;
    mode=true;
    this->setWindowTitle("My Notepad");
    this->setWindowIcon(QIcon(":/src/imgs/paste.png"));

    loadPosition();

    //QDesktopServices cho phép ta dùng các method để truy desktop services
    //QDesktopServices::openUrl(QUrl("file:///C:\\Users\\Admin\\Desktop\\New folder\\ê.txt", QUrl::TolerantMode));

    //phân biệt url và path:path là đường dẫn đến 1 file trong cây thư mục. url là đường link đến bất kỳ 1 nơi nào đó
    //url có 1 thứ gọi là scheme-> nó là tiền tố xác định type của url(setScheme()).Ví dụ ở trên thì scheme là (file://)
    //trong web mặc định scheme(type) của url là http://. relative url là url k có scheme, absolute url có scheme. Ta có thể
    //kiểm tra bằng isRelative or scheme().isEmpty(); Nó khác vs đường dẫn tuyệt đối or tương đối->QDir::isRelativePath()
    //khi thao tác với cây thư mục, ta có thể có đg link đến file nào đó, ta dùng url.path() để lấy path của url thì tùy vào
    //url là relative hay k thì cái path đó là relative hay absolute

    //mở kèm 1 file khác bằng trình mặc định sẵn trong máy
    //    on_actionOpen_triggered();
    //có thể đặt ở đây để mở Ct là sẽ yêu cầu mở file nào, nhưng nếu muốn file trống thì cái này lại k hay
    //    load("C:\\Users\\Admin\\Desktop\\New folder\\ê.txt");
    //có thể đặt hàm load ở đây để mặc định luôn mở file này, cx chưa hay bằng lấy argument kia

#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)//hay
    ui->actionPrint->setEnabled(false);
#endif
    //defined là các thư viện ta đã thêm chưa or define nó chưa, còn QT_CONFIG là xem máy tính có hỗ trợ k
#if !QT_CONFIG(clipboard)//rất hay
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif
    //kiểm tra trong máy có hỗ trợ clipboard và in k, nếu máy k hỗ trợ thì k dùng các tính năng này tránh lỗi
    //chỉ cần chú ý 2 tính năng clipboard và print
}

void MainWindow::load(QString path)
{
    file.setFileName(path);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","File not open !");
        return;
    }
    QTextStream in(&file);
    setWindowTitle(path);
    in.setCodec("UTF-8");//hàm này cho phép cái stream lưu dữ liệu mã hóa ntn, mặc định sẽ gọi QTextCodec::codecForLocale()
    //tức là cái phù hợp nhất cho locale. Set UTF-8 mà để mặc định đều ok
    //QDataStream thì setVersion còn QTextStream thì setCodec
    QString textContent=in.readAll();
    ui->textEdit->setText(textContent);
    //Khi dùng qDebug() với string thì dùng ô k đc ố, hiển thị thì sẽ \n; Khi dùng qDebug() với const char* thì ô cx k đc
    //còn hiển thị \n có xuống dòng. Nhưng điều đó kqtr-> qtr là giao diện textEdit nó dùng đc hết dù ô hay ố và cả \n.
    //Đó là đúng trong mọi TH, k bh in đc tv vs debug.

    //Khi muốn đọc ghi file thì k thể dùng tv với write,read đc.
    //Nếu muốn đọc ghi file tiếng việt thì text để lưu buộc là QString k dùng const char* với QTextStream
    //có thêm 1 lý do nx để dùng stream lưu nội dung file là ghi đc tv
    //Nếu dùng QDataStream thì lưu ok hết
    file.close();
    isOpen=true;
}

MainWindow::~MainWindow()
{
    savePosition();
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    setWindowTitle("New");
    current_path.clear();
    ui->textEdit->setText(QString());
    isOpen=false;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath=QFileDialog::getOpenFileName(this,"Choose file to open");
    current_path=filePath;
    file.setFileName(filePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","File not open !");
    }
    else{
        QTextStream in(&file);
        setWindowTitle(filePath);
        in.setCodec("UTF-8");
        QString textContent=in.readAll();
        ui->textEdit->setText(textContent);
        isOpen=true;
    }
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    if(isOpen==false)
    {
        QString file_name=QFileDialog::getSaveFileName(this,"Save Dialog");
        current_path=file_name;
        file.setFileName(file_name);
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            return;
        }
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << ui->textEdit->toPlainText();
        file.flush();
        file.close();
        isOpen=true;
    }
    else
    {
        file.setFileName(current_path);
        setWindowTitle(current_path);
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            return;
        }
        QTextStream out(&file);
        out.setCodec("UTF-8");
        QDataStream data;
        out << ui->textEdit->toPlainText();
        file.flush();
        file.close();
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString path=QFileDialog::getSaveFileName(this,"Save Dialog");
    current_path=path;
    setWindowTitle(current_path);
    file.setFileName(path);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << ui->textEdit->toPlainText();
    file.flush();
    file.close();
    isOpen=true;
}

void MainWindow::on_actionClose_triggered()
{
    qApp->exit();
}

void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();//vô bộ đệm clipboard trong máy
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionAbout_App_triggered()
{
    QString aboutApp( "Author: NTH \n" + tr("Date: 23/10/2020 \n") + "This app is create for fun!\n\n"
                       + "***** Have a nice day *****");
    QMessageBox about(this);
    about.setText(aboutApp);
    about.exec();
    //có thể exec cái message box như này
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();//có hàm kiểm tra undo/copy/redoAvailable là signal kiểm tra, từ đó ta có thể enable cái action hay k
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionColor_triggered()
{
    colorTextFix= QColorDialog::getColor(Qt::red,this,"Color Dialog");
    if(colorTextFix.isValid())
    {
        ui->textEdit->setTextColor(colorTextFix);//Cái set color này nó đè lên css(styleSheet)
        //cái này nó chỉ set current format thôi, nếu ta move cursor vào chỗ khác thì sẽ mang format chỗ đó
        //bên cạnh đó nó cx bị lỗi unicode nếu gõ â ngay đầu tiên chẳng hạn thì nó quay về format cũ
        //ta fix điều đó bằng signal currentCharFormatChanged lấy color cũ, lưu color vào biến
        connect(ui->textEdit,&QTextEdit::currentCharFormatChanged,this,[&]()
        {
            ui->textEdit->setTextColor(colorTextFix);
        });

        //Đó là ta set màu cho phần chữ đc chọn và phần chữ viết tiếp, nếu set màu toàn bộ thì có thể dùng
        //styleSheet, QPalette or làm thủ công như này:
        //        ui->textEdit->selectAll();
        //        ui->textEdit->setTextColor(color);
        //        QTextCursor cursor = ui->textEdit->textCursor();//lưu vị trí cursor trên 1 văn bản text
        //        cursor.movePosition( QTextCursor::End );//để bỏ chọn select all bên trên
        //        ui->textEdit->setTextCursor(cursor);
    }
}

void MainWindow::on_actionHighlight_triggered()
{
    if(ui->textEdit->textBackgroundColor()!=Qt::green)
        ui->textEdit->setTextBackgroundColor(Qt::green);
    else ui->textEdit->setTextBackgroundColor(Qt::transparent);//hay vì ấn thì hightlight, ấn tiếp thì un highlight
}

void MainWindow::on_actionFont_triggered()
{
    bool ok=true;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok){
        //Mỗi widget đều có styleSheet là code css giúp ta format gần như pro cái widget của ta. Chúng thg có code khác
        //nhau nên k thể ốp css của button cho label đc chẳng hạn.
        //Khi setStyleSheet("") cho textEdit thì html của nó tự động cập nhật code tương ứng vs style sheet đó.
        //font gà hơn color vì nó bị stylesheet đè lên, nếu ta setStyleSheet cho nó về font thì ta thêm QFont về sau nó
        //k đè lên styleSheet đc, k đổi gì
        ui->textEdit->setFont(font);
        //ta muốn bđ có 1 font mặc định, nếu k chỉnh sửa gì thì dùng font đó, nếu chỉnh sửa thì đổi sang font mới
        //=>k set font cho stylesheet và cả lúc chuyển sáng tối, chỉ cần set font là đc r
    }
}

void MainWindow::on_actionMode_triggered()
{
    /*QColor color=QColorDialog::getColor(Qt::white,this,"Choose color");
    QColor color1(0,255,0,255);
    QColor color2(Qt::red);
    QColor color3("#6A5ACD");
    //đủ kiểu khai báo màu
    QPalette palette;
    palette.setColor(QPalette::Base,color3);//base là tô nền
    palette.setBrush(QPalette::Active, QPalette::Text, QBrush(color));
    if(color.isValid())
    {
        ui->textEdit->setPalette(palette);//hàm set cho cái bảng màu, tô cj
        QMessageBox::information(this,"title", "error2");
    }
    else
    {
        QMessageBox::information(this,"title", "error");
     }//có thể dùng QPalette or css chỉnh màu, nhưng cần chú ý styleSheet bị fix như font thì k dùng.
    //Cách dùng QPalette chỉnh màu-> ta chỉ cần setColor và setBrush cho QPalette thì trong đó có enum ColorGroup và
    //ColorRole là đủ vai trò tô bất cứ cái gì ở trong widget r-> setPalette nx là xong*/

    //hàm setTextColor của QTextEdit dùng để bôi màu cho chỗ chữ nào or viết tiếp sẽ có màu nào, còn dùng css or QPalette
    //có thể set màu cho toàn bộ textedit luôn, thay đổi thuộc tính của nó luôn
    if(mode){
        ui->textEdit->setStyleSheet("background-color: rgb(0,0,0); color:white");//k set font ở đây
        mode=false;
    }
    else{
        ui->textEdit->setStyleSheet("background-color: rgb(255,255,255); color:Black");
        mode=true;
    }
}

void MainWindow::on_actionPrint_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    //ví dụ có 1 textEdit chứa chữ, để in nó ra ta làm theo thứ tự: QPrinter set tất cả các định dạng đầu ra->QPrintDialog khởi
    //tạo truyền cái printer đó vào r exec để ng dùng nhập thông số->textEdit->print(QPrinter)->xong
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif // QT_CONFIG(printdialog)
    //    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
    //k dùng đc vì QPrintDialog yêu cầu phải kết nối với máy in. Nhớ thêm printsupport vào pro file
    //ta chỉ cần lợi dụng QPrinter vs hàm print của textEdit để chuyển định dạng từ file text sang file pdf.

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
    //QFileInfo(filename) lấy thông tin file gì bất cứ lúc nào

    QPrinter printer(QPrinter::PrinterResolution);//lấy resolution trùng với màn hình = QPrinter::ScreenResolution
    //QPrinter là ta set định dạng đầu ra, kích thước, tên file đầu ra.
    //Còn QPrinterDialog thì là dialog của máy in r
    printer.setOutputFormat(QPrinter::PdfFormat);
    //    printer.setPaperSize(QPrinter::A4);//hàm setPaperSize lỗi thời r dùng setPageSize
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(fileName);
    ui->textEdit->print(&printer);//hàm print ở trong QTextEdit lấy cái printer set format r
}

void MainWindow::loadPosition()
{
    QSettings setting("My Company","My App");

    setting.beginGroup("MainWindow");
    QRect myrect = setting.value("position",QVariant(QRect(50,50,500,400))).toRect();
    //ta truyền vào giá trị mặc định sẽ lưu ở mỗi value nếu chưa set j sẽ lấy. Nếu k có mặc định mà gọi load lần
    //đầu thì nó sẽ lấy position là myrect 0,0,0,0 và k hiện gì cả. value trả ra QVariant cast sang đúng biến ta lưu là đc
    setGeometry(myrect);

    setting.endGroup();
}

void MainWindow::savePosition()
{
    //biến QSettings lưu các setting của app ta dùng cho lần sử dụng kế. Ta truyền vào tên công ty và tên sản phẩm
    //thì mỗi công ty và sp có tên khác nhau sẽ lưu các setting khác nhau, và nó fix lưu trong hệ thống, ta cứ tạo
    //các biến setting khác có tên organization và app tương tự là gọi đến nó
    QSettings setting("My Company","My App");

    setting.beginGroup("MainWindow");
    setting.setValue("position",this->geometry());//lưu biến gì ở thời điểm gọi và có thể lấy biến đó ra
    //mọi thao tác đều lưu trong group, nó quyết định ta chỉnh setting của cái gì, có thể chỉnh setting cho cả cửa sổ
    //or chỉ là cho thanh panel thì begin 2 group khác nhau. 1 group có thể set nh value. Ở đây ta chỉ để nó lưu vị trí
    //nó sẽ lưu kiểu MainWindow/position, or nếu ta lưu thêm MainWindow/fullScreen chẳng hạn
    setting.endGroup();
    //hàm này để ở hàm destructor để nó lưu
    //hàm clear sẽ xóa các thiết lập
}

void MainWindow::on_actionFind_triggered()
{
    findDialog->show();
    connect(findDialog,SIGNAL(find(QString)),this,SLOT(find(QString)));
}

void MainWindow::find(QString text)
{
    if(!ui->textEdit->find(text))
    {
        QTextCursor cursorFind;
        cursorFind.movePosition(QTextCursor::Start);
        ui->textEdit->setTextCursor(cursorFind);
        ui->textEdit->find(text);
        //ham find tự động tìm kiếm ký tự trùng tiếp theo, ta chỉ cần set cursor nó đến cuối thì quay 1 vòng
    }
}
