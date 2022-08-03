#include <QCoreApplication>
#include <QtCore>
#include <QPixmap>
#include <QString>
#include <QFile>
#include <QTextStream>

void write(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Cannot Open File!";
        return;
    }

//    QTextStream out(&file);//QTextStream là interface để ghi/đọc tất cả dạng text cho IODevice k chỉ mỗi ghi file đâu
//    out << "Hello World ố ! \n !!";
//    file.flush();//QFileDevice là lớp cha virtual của QFile có flush, QTextStream cx có flush dùng nào cx đc

    QString str="Hello World! ố \n !!";
    const char* charFromString=qPrintable(str);//tương ứng vs c_str() của c++
    file.write(charFromString);//dùng write thì vs const char * của QIODevice cho phép mọi device đều đoc/viet đc

    file.close();
}

void read(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Cannot Open File!";
        return;
    }

//    QTextStream in(&file);
//    in.setCodec("UTF-8");
//    QString content=in.readAll();//sai
//    in >> content;//vs string viết tv ntn

    //nếu dùng QDataStream thì k cần QFile::Text còn QTextStream buộc phải specific nv
//    QString line;
//    do{
//        line = file.readLine();
//        qDebug() << line;
//    }while(!line.isEmpty());//có thể đọc từng dòng-> chú ý isEmpty khác với isNull

    QString content=file.read(100);//or read(char*,int) ; QIODevice cx có readAll luôn
    qDebug() << content;

    file.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << QDir("img").exists();//qDebug tự động xuống dòng
    qDebug() << QDir("/img").dirName() << QDir().dirName();// "/img" là tuyệt đối vì / là root ổ cứng, "img" là tương đối
    //QDir() = QDir("") = QDir(".") != QDir("/")

    QDir directory("Documents/Letters");//tạo ra 1 cái biến lưu tên(k cần phải tồn tại),tương đối sẽ cùng cấp debug folder
    QString path = directory.filePath("contents.txt");//tạo k check(tg đối)
    QString absolutePath = directory.absoluteFilePath("contents.txt");//lấy đường dẫn tuyệt đối
    //có thể k tồn tại mà chỉ là t tạo ra. Bản chất QDir QFile lưu mọi đường dẫn chứ có phải chỉ đg dẫn tồn tại đâu
    qDebug() << path << " " << absolutePath;

    QString s;
    s = QDir("/home/bob").relativeFilePath("images/file.jpg");     // s is "images/file.jpg"
    s = QDir("/home/bob").relativeFilePath("/home/mary/file.txt"); // s is "../mary/file.txt"
    //chú ý các ham filepath,relavefilepath hay absolutefilepath nó chỉ tạo và lưu chứ k check

    if (!directory.exists())
        qWarning("Cannot find the example directory");

    QDir dir = QDir::root();                 // "/"
    if (!dir.cd("tmp"))    //đi đến thư mục nào đó từ dir ("/tmp")
    {
        qWarning("Cannot find the \"/tmp\" directory");
        //muôn in " thì dùng \". Dùng / or \\ đều ok vì \ là dấu trong code mất r
    }

    QDir testSort;
    testSort.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);//các file kể cả file ẩn k dùng symbolic link
    testSort.setSorting(QDir::Size | QDir::Reversed | QDir::Time);//theo thứ tự ngươc dùng cho entryList

    QFileInfoList list = testSort.entryInfoList();//lấy list QFileInfo, khác entryList chỉ lấy tên QStringList
    for (int i = 0; i < list.size(); ++i)//lấy số lượng của list, khác với size của QFileInfo là lấy byte của file
    {
        QFileInfo fileInfo = list.at(i);//lấy vị trí trong list
        qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(),10)//lấy byte của 1 File
                                                .arg(fileInfo.fileName()));//lấy tên của file
        //qDebug() in const char* k có "" nhưng in QString thì có như kiểu trích dẫn
    }

    QDir testCanonical("../../");
    QString stringCanonical=testCanonical.canonicalPath();
    qDebug() << stringCanonical;//lệnh biến đường dẫn hiện tại thành đường dẫn tuyệt đối duy nhất bỏ các ký tự '.', '..'

    qDebug() << QDir().homePath();
    qDebug() << QDir().tempPath();
    qDebug() << QDir().currentPath(); // là QDir("") or QDir k khai báo gì cả
    if(QDir().root().isRoot())  //cx chỉ là QDir("/") root ổ cứng
    qDebug() << QDir().rootPath() << "is a root link";

    QStringList filters;
    filters << "*.Debug" << "*.stash" << "*.cc";//cách thêm vào stringlist
    QDir testCurrent=QDir().current();//home(),root(),temp() nx
    testCurrent.setNameFilters(filters);
    foreach(QFileInfo fi,testCurrent.entryInfoList())
    {
        if (fi.isDir())
        qDebug() << "Dir: " << fi.absoluteFilePath();//chứa cả file còn absolutePath k chứa file
        //entryInfoList chứa cả thu muc hiện tại và thư mục chứa thư mục hiện tại,sau đó mới là các thành phần trong current
        if(fi.isFile())
        qDebug() << "File: " << fi.absoluteFilePath();
        //pb absoluteFilePath của QDir tạo đường dẫn ảo bất chấp tồn tại k, còn absoluteFilePath của QFileInfo in ra đường
        //dẫn của nó bth mà thôi
    }

    QDir::setSearchPaths("icons", QStringList(QDir::homePath() + "/images"));
    QDir::setSearchPaths("docs", QStringList(":/embeddedDocuments"));//tìm trong file resource qrc
    //QDir còn có hàm giúp lưu Path phục vụ cho vc tìm kiếm. Đối số 1 là prefix là tiền tố mà ta muốn search, đối số 2 là
    //QStringList lưu các đường dẫn mà sẽ tìm ở trong đó.
    QPixmap pixmap("icons:undo.png"); // will look for undo.png in QDir::homePath() + "/images"
    QFile file("docs:design.pdf"); // will look in the :/embeddedDocuments resource path
    //Để dùng, khi cần lưu 1 cái gì ví dụ tìm 1 file nhưng chỉ tìm file đó ở những cái đường dẫn mà ta muôn như ở trên thì ta
    //dùng "<tên prefix>:<tên file>" thì cái prefix kia đc gán 1 string list để tìm ở bên trên r

    // The current directory is "/usr/local"
    QDir d1("/usr/local/bin");
    d1.setFilter(QDir::Executable | QDir::System | QDir::NoDotDot);
    QDir d2("bin");
    if (d1 != d2)
        qDebug("They differ");
    else if(d1==d2)
    {
        qDebug() << "They are the same";
    }
    //chỉ cần khác filter hoặc khác tên path

    foreach(QFileInfo fi,QDir().drives())
    {
        qDebug() << fi;//QFileInfo in trực tiếp đc luôn mà k cần absoluteFilePath() cx ok,in tên thôi
    }

    QDir cwd;
    if(!cwd.exists("img/imgInside"))//kiểm trả bên trong directory có cj
    {
        cwd.mkpath("img/imgInside");//tuyệt đối cx đc. Trả về true false
        //mkpath tạo tất cả kể cả các thư mục để có đến đc cái thư mục con, còn mkdir chỉ tạo 1 thư mục con
        qDebug() << "Created";
    }
    else
    {
        qDebug() << "Already existed";
    }

    //Ngoài ra còn có marco quản lý vc load hay unload resource dùng trong ct
    //cdUp,count,filter,isAbsolute,isEmpty,isReadable,makeAbsolute,nameFilter,path,refresh,remove,listSeparator,separator
    //,remove,removeRecursively,rename,rmdir,rmpath,setPath,swap,match,addSearchPath,isAbsolutePath,temp
    //(setFilter là set các giá trị enum Filter đặc biệt cho biến,setNameFilters là set theo cấu trúc đuôi nào mà ta muốn
    //dùng)/(isAbsolute kiểm tra QDir có đường dẫn là Absolute hay k,còn isAbsolutePath là static kiểm tra QString bky)/
    //(setSearchPaths bắt đầu gán còn addSearchPath sẽ gán thêm vào prefix đó)/(separator lấy ký tự ngăn cách các thư mục(
    //trong win là /),còn listSeparator trả về dấu ngăn cách danh sách đường dẫn(win là ;))

    QString fileName="testFile.txt";
    write(fileName);
    read(fileName);

//    read(":/new/prefix1/masterQDirAndQFile.pro");//qrc là xml file, compile data at run time

    return a.exec();
}
