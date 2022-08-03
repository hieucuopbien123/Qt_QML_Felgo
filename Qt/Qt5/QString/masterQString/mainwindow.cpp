#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    static const QChar data[4] = { 0x0055, 0x006e, 0x10e3, 0x03a3 };
    QString str(data, 4);//gán cho str 4 phần tử đầu của mảng char
    //Kiểu dữ liệu QString là chuẩn nhất để lưu dữ liệu và dùng, các hình thức khác nên quy về kiểu này trừ khi cần dùng
    //đặc biệt. Các kiểu khác QLatin1String(là 1 luôn),const char*,const QByteArray

    QString str1;
    str.resize(4);
    str1[0] = QChar('U');
    str1[1] = QChar('n');
    str1[2] = QChar(0x10e3);
    str1[3] = QChar(0x03a3);

    QString str2 = "and";
    str2.prepend("rock ");
    str2.append(" roll");
    str2.replace(5, 3, "&");//thế ký tự

    QString str3 = "We must be <b>bold</b>, very <b>bold</b>";//nó dùng đc HTML
    int j = 0;
    while ((j = str3.indexOf("<b>", j)) != -1) {//trả về -1 nếu thất bại,2 là kiểm tra kể từ ký tự nào
        qDebug() << "Found <b> tag at index position" << j;
        ++j;
    }

    QString url = QLatin1String("http://www.unicode.org/");
    //QString thực chất dùng TT vs 8-bit string nếu k sợ risk là k đúng loại 8-bit string, or nếu sơ thì dùng từ QLatin1String
    //QLatin1String và QString dùng như nhau

    QString hello("hello");
    QStringRef el(&hello, 2, 3);
    //cách nhớ, thông thường sẽ là (<cái gì hiện ra là chính>,<apply cj vào đối số 1>) và (<từ đâu>,<bao nhiêu>)
    QLatin1String world("world");
    QString message =  hello % el % world % QChar('!');
    //khi dùng #include <QStringBuilder> thì có thể dùng % thay thế cho + và như thế sẽ tối ưu bộ nhớ(+sẽ phân bổ nhiều bộ nhờ còn %
    //thì nó chỉ thêm vào theo kiểu xđ kết quả 1 bộ nhớ QString cuối cùng nên tối ưu hơn)
    //QStringRef giúp trỏ đến 1 phần chuỗi=>tối ưu tránh phải khởi tạo vùng nhớ mới(k có hàm nào làm đổi chỗ nó=>read-only)

    QString x = "free";
    QString y = "dom";
    x.append(y);
    //nó tương đương vs x.insert(x.size(), y);

    QString i;           // current file's number
    QLatin1String total;       // number of files to process
    QStringView fileName;    // current file's name//cx như QStringRef readonly nhưng nó là UTF-16=> nch mấy cái này như nhau
    QString status = QString("Processing file %1 of %2: %3")
                    .arg(i).arg(total).arg(fileName);
    //Dùng arg ta có thể thay thế vị trí chỉ định ntn, nó rõ ràng hơn dùng replace(khi đã có chuỗi rồi).
    //arg bth nhận 3 đối số,2 là int ít nhất bao nhiêu ký tự lấy từ ký tự 1, nếu ký tự 1 có số ký tự ít hơn thì thế bằng QChar(đối sô 3)

    str = QString("Decimal 63 is %1 in hexadecimal")
            .arg(63, 0, 16);
    // str == "Decimal 63 is 3f in hexadecimal"
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    str = QString("%1 %L2 %L3")//L là biểu diễn địa phương của số tùy vùng, L bị bỏ qua khi gặp base 10.
            //chỉnh địa phương bằng setDefault của QLocale
            .arg(12345)
            .arg(12345)
            .arg(12345, 0,);
    // str == "12345 12,345 3 16039"

    double d = 12.34;
    QString str4 = QString("delta: %1").arg(d, 0, 'E',3,QChar('1'));
    //khi là số int thì QChar thành 4 còn 3 là base.Khi là double thì QChar thành 5, 3 là format(mặc định là g),4 là precision
    // str == "delta: 1.234E+01"

    str4 = "%1 %2";
    str4.arg("%1f", "Hello");        // returns "%1f Hello"
    str4.arg("%1f").arg("Hello");    // returns "Hellof %2"
    //nếu dùng nhiều đối số có lợi là nó sẽ gán theo thứ tự marker % (1-99).Còn gán bth cx đc nhưng nếu có TH nó vô tình gây ra %<marker>
    //như trong TH trên gây ta %1f %2 thì nó KT r lại gán tiếp vào %1

    str4 = "%1%3%2";
    str4.arg("Hello").arg(20).arg(50); // returns "Hello500"
    //kiểu truyền từng cái 1 này mà có nh arg sẽ gây lỗi nếu viết liền. Vì nếu vô tình gây ra marker lớn hơn thì nó sẽ thế vô marker lớn
    //ví dụ ở đây: Hello%320 thì 50 sẽ thế vô %32 do 32 trong 1-99 và lớn hơn %3 do vô tình tạo ra thì nó sẽ lấy
    str4 = "%1%2%3";
    str4.arg("Hello").arg(50).arg(20); // returns "Hello5020"=> buộc phải thế này nếu dùng cách cũ
    //tuy nhiên nếu dùng cách ms thì k phải lo j hết truyền đối số liên tiếp bao nhiêu cx đc. Mỗi tội truyền kiểu cũ đc phép truyền số,
    //còn kiểu mới thì buộc sang string
    str4 = "%1%3%2";
    str4.arg("Hello", QString::number(20), QString::number(50)); // returns "Hello5020"

    QString str5("LOGOUT\r\n");
    str.chop(2);// str == "LOGOUT"=>xóa từ đít

    int m = QString::compare("aUtO", "AuTo", Qt::CaseInsensitive);  // m == 0//so sánh trong bảng ASCII nhưng tùy sensitivity
    int n = QString::compare("auto", "Car", Qt::CaseSensitive);     // n > 0
    int p = QString::compare("auto", "Car", Qt::CaseInsensitive);   // p < 0

    QString str6 = "Peter Pan";
    str6.contains("peter", Qt::CaseInsensitive);// returns true

    str6 = "banana and panama";
    str6.count(QRegExp("a[nm]a"));    // returns 4// đếm số lần xh,hoặc n hoặc m
    str6.count(QRegularExpression("a[nm]a"));    // returns 4//2 cái này gần giống nhau//count k sẽ ra số lượng kí tự

    str6 = "Hello world";
    QChar *abc = str6.data();//trả về mảng QChar trỏ đến QString(lấy QChar* từ QString)
    QChar qwe=str6.data()[0];
    while (!abc->isNull()) {
        qDebug() << abc->unicode();//trả về GT nguyên unicode(cả QString QChar đều có)
        ++abc;//tức sang ký tự tiếp theo, mảng cộng như v là sang ký tự next, đúng hơn là +=kích thước nhưng QChar kich thước là 1
        //nó take 2byte unicode và return 1byte version of nó. cx như QChar.toASCII()->sai con trỏ cộng thì sang ô nhớ next
        //QString unicode sẽ cho ra QChar*, QChar* unicode sẽ ra int trong bảng unicode/toASCII thì ra bảng ASCII
    }

    str = "Bananas";
    str.endsWith("anas");         // returns true
    bool testEndsWith=str.endsWith("pple");         // returns false

    str = "Berlin";
    str.fill('z');
    // str == "zzzzzz"
    str.fill('A', 2);
    // str == "AA"

    QRegularExpression pattern("\u00A4");
    static const QChar unicode[] = {
            0x005A, 0x007F, 0x00A4, 0x0060,
            0x1009, 0x0020, 0x0020};
    int size = sizeof(unicode) / sizeof(QChar);
//    str.setRawData(unicode, size); k là static còn fromRawData thì là static
    str=QString::fromRawData(unicode,size);
    if (str.contains(pattern)) {
        // ...
    }
    //fromRawData tạo ra QString từ const QChar*,size là số phần tử muốn lấy. Khi chuỗi đc tạo ra thì k thể copy or sửa đổi
    //ng ta thg dùng setRawData tương tự nếu k muốn tạo ra 1 string kiểu copy như trên mà tái sử dùng QString có sẵn, nó k phải static

    //setRawData và vc khởi tạo copy QString(<const QChar*>,size) khác nhau. setRawData tạo shallow copy(vẫn còn mỗi liên hệ
    //vs original),còn khởi tạo bth là deep copy(copy và rời hoàn toàn khỏi original). khi setRawData thì QString bị xóa đồng
    //nghĩa const QChar* cx k còn. Còn vì sao cần gán const QChar* cho QString thì chưa cần bt

    //fromRawData thì địa chỉ r. Dùng setUnicode để resize và gán copy.setUnicode(NULL,int) thì sẽ resize kích thước mà k gán gì cả


    QString s1 = "sticky question";
    QString s2 = "sti";//or QLatin1String cx dc
    s1.indexOf(s2);               // returns 0
    s1.indexOf(s2, 1);            // returns 10
    s1.indexOf("sti", 11,Qt::CaseInsensitive); // returns -1

    str = "the minimum";
    str.indexOf(QRegExp("m[aeiou]"), 0);       // returns 4

    str = "the minimum";
    QRegularExpressionMatch match;
    str.indexOf(QRegularExpression("m[aeiou]"), 0, &match); // returns 4, nếu 3 khác null nó lưu KQ vào biến QRegularExpressionMatch
    // match.captured() == mi

    x = "Pineapple";
    y = x.left(4);      // y == "Pine"

    QString s = "apple";
    QString t = s.rightJustified(8, '.');    // t == "...apple"
    //nó nhận 3 đối số, 1 là số phần tử lấy từ chuỗi,nếu nhiều hơn thì sẽ bù bằng 2.3 là biến boolean truncate.
    //Khi nó size string nó dài hơn 1 mà true thì sẽ cắt, ít hơn thì sẽ return copy cả string

    //cái trên tính từ 1 thì cái này tính từ 0(index)
    QString o = "Nine pineapples";
    QString k = o.mid(5, 4);            // y == "pine"
    QString l = o.mid(5);               // z == "pineapples"
    QStringRef w = o.midRef(5, 4);      // y == "pine"
    QStringRef z = o.midRef(5);         // z == "pineapples"
    x = "Pineapple";
    QStringRef testref = x.rightRef(5);   // y == "apple"
    //cx thế chỉ là trả về QStringRef

    long a = 63;
    t = QString::number(a, 16).toUpper();     // t == "3F"//đổi sang hệ 16 ở QString nên vẫn là chuỗi chữ kp số nên viết hoa lên đc

    x = "ship";
    y = "air";
    x.prepend(y);// x == "airship"

    s = "Montreal";
    s.remove(1, 4);// s == "Meal" tính từ index 0
    t = "Ali Baba";
    t.remove(QChar('a'), Qt::CaseInsensitive);// t == "li Bb"//có thẻ truyền số or ký tự or QRegExp tùy TH muốn xóa
    QString r = "Telephone";
    r.remove(QRegExp("[aeiou]."));// r == "The"//dấu chấm thay thế cho bất kì 1 ký tự nào,giông ?. Tức ở đây ta xóa liền 2 ký tự 1 lúc
 //r.remove(QRegularExpression("[aeiou]."));

    str="ab";
    str.repeated(4);// returns "abababab"

    str = "colour behaviour flavour neighbour";
    str.replace(QString("ou"), QString("o"));// str == "color behavior flavor neighbor", 3 mặc định QCaseSensitive nx
    QString equis = "xxxxxx";
    equis.replace("xx", "x");// equis == "xxx" chữ thế vào k bị rescan

    t = "A <i>bon mot</i>.";
    t.replace(QRegularExpression("<i>([^<]*)</i>"), "\\emph{\\1}");
    // t == "A \\emph{bon mot}.". Dùng TT với siêu VB
    //QRegExp: dấu () k ảnh hưởng,^ tức là phủ định bộ ký tự nào, tức là ta sẽ k tính nó cho đến khi gặp < ở TH này.* biểu thị cho bất
    //kì 1 chuỗi ký tự nào.Ở đây ta đặt [] có nghĩa là bắt tất cả Ký tự ở bên trong trong chuỗi. Ở đây tức bắt tất cả ký tự trừ<ta dùng
    //[] như 1 đk.regexp muốn include \ thì dùng \\ ở 2, còn muốn match vs \ thì \\\\ ở 1.Dùng \\1 để tạo \1 sẽ reference vào QString ntn

    t.squeeze();//giải phóng bộ nhớ k cần thiết để lưu ký tự(ít dùng vì nó tự khi kết thúc CT)

    s = "Hello world";
    s.resize(5);
    // s == "Hello"
    s.resize(8);
    // s == "Hello???" (where ? stands for any character)

    t = "Hello";
    r.resize(t.size() + 10, 'X');
    // t == "HelloXXXXXXXXXX" chủ động hơn leftJustified nh khi cx có thể fill cụ thể bao nhiêu

    QString str9;
    QString csv = "forename,middlename,surname,phone";
    QString path = "/usr/local/bin/myapp"; // First field is empty
    QString::SectionFlag flag = QString::SectionSkipEmpty;
    str9 = path.section('/', 3, 4);  // str == "bin/myapp"
    str9 = path.section('/', 3, 3, flag); // str == "myapp"//bỏ trống

    str = csv.section(',', -3, -2);  // str == "middlename,surname"//khi chuỗi quá dài=> count từ phải qua thì từ -1, trái thì 0
    str = path.section('/', -1); // str == "myapp"

    QString line = "forename\tmiddlename  surname \t \t phone";
    QRegExp sep("\\s+");//siêu văn bản thì tính thẻ như chữ bth còn ký tự đb\t,\n nó là 1 ký tự trong ascii nên dịch nó r ms dùng regexp
    str = line.section(sep, 2, 2); // str == "surname"
    str = line.section(sep, -3, -2); // str == "middlename  surname"
    //\s là space nhưng ta phải tạo ra nó khi compile chứ kp là dùng \s luôn, dấu + tức là tính cả space liên tiếp
    //QRegExp dùng như QRegularExpression

    str.setNum(1234);       // str == "1234"
    //pb:lấy số thì toInt(),toDouble().Lấy Qstring thì number() là static,setNum() là function của string
    //toInt() 1 là bool* nếu k dùng nullptr, thất bại hay k sẽ trả ra,2 là base còn chấm động thì chỉ có mỗi bool
    //number thì số là số và base, chấm động thì là số, format(g,e,E,..),và precision giống hệt setnum
    //setNum(số,base/số,format,precision)=>cứ nhớ int có base, chấm động theo thứ tự format,precision

    str = "  lots\t of\nwhitespace\r\n ";
    str = str.simplified();
    // str == "lots of whitespace";

    str = QStringLiteral("a,,b,c");
    //khi khai báo chuỗi vs "" là đã có sự chuyển đổi ngầm định từ const char* sang QString, r QStringData sẽ copy cái string đó theo
    //kiểu cấp vùng nhớ. Sau đó nó đc chuyển vô UTF-8 or UTF-16.Nếu dùng QLatin1String sẽ nhanh hơn do specify cái UTF r, tuy nhiên qtr
    //là vùng nhớ đc cấp phát quá nhiều mỗi lần dùng chuỗi "" đồng thời cx tránh conversion to QString
    //=> dùng QStringLiteral sẽ compile nó at run time(),nó là 1 marco và readonly,và sẽ tốt hơn do tránh allocation
    QStringList list1 = str.split(QLatin1Char(','));
    // list1: [ "a", "", "b", "c" ]
    QStringList list2 = str.split(QLatin1Char(','), Qt::SkipEmptyParts);
    // list2: [ "a", "b", "c" ] chia string thành nhiều QString lưu vào list, dùng at để truy xuất, truyền biến cờ có skip space k

    str = "abc";
    auto parts = str.split(QString());
    // parts: {"", "a", "b", "c", ""} nó tự thêm empty vào đầu cuối
    str = "/a/b/c/";
    parts = str.split(QLatin1Char('/'));
    // parts: {"", "a", "b", "c", ""}

    QStringList list;
    str = "This time, a\n normal English sentence.";
    list = str.split(QRegExp("\\W+"), Qt::SkipEmptyParts);
    // list: [ "This", "time", "a", "normal", "English", "sentence" ]//w là ký tự chữ, số, W là ngoại trừ những cái đó, pb vs \\b
    //\n \t nó cx coi như khoảng trắng.QRegExp có 1 bảng riêng cho các ký tự, k dùng tới ASCII

    str = "Now: this sentence fragment.";
    list = str.split(QRegExp("\\b"));
    // list: [ "", "Now", ": ", "this", " ", "sentence", " ", "fragment", "." ]
    //\b là word boundary.Chỉ lấy ký tự kẹp giữa \b(nếu có 1 \b thì từ đó đến hết) VD \bOK\b thì lấy Its OK nhưng ItsOK thì k vì OK phải
    //separate là 1 từ or 1 ký tự đặc biệt ko là sô và chữ như dấu : ở bên trên.
    //Còn \B thì ngc lại k lấy 1 từ mà lấy 1 phần từ khác. Ở đây nó sẽ split toàn bộ kể cả space

    str = "Bananas";
    str.startsWith("Ban");     // returns true
    str.startsWith("Car");     // returns false

    str = "1234.56";
    double val = str.toDouble();   // val == 1234.56

    bool ok;
    double num;
    num = QString( "1234.56e-02" ).toFloat(&ok); // ok == true, d == 12.3456 bool k dùng nullptr nó ms trả về
    num = QString( "1234.56e-02 Volt" ).toDouble(&ok); // ok == false, d == 0
    d = QString( "1,234,567.89" ).toDouble(&ok);//ok == false nếu dùng QLocale::toDouble mà set là VN thì sẽ dùng đc dấu phẩy,default là C
    d = QString( "1234.56" ).toDouble(&ok); // ok == true, d == 1234.56

    QString plain = "#include <QtCore>";
    QString html = plain.toHtmlEscaped();
    // html == "#include &lt;QtCore&gt;" chuyển đổi bộ plaintext thành HTML text

    str = "FF";
    long hex = str.toLong(&ok, 16);     // hex == 255, ok == true
    long dec = str.toULongLong(&ok, 10);     // dec == 0, ok == false chuyển int phải đúng base TT VD toUShort toInt toLong

    str = "The Qt PROJECT";
    str = str.toLower();        // str == "the qt project"

    str = "  lots\t of\nwhitespace\r\n ";
    str = str.trimmed();
    // str == "lots\t of\nwhitespace" nó chỉ bỏ space ở start và end kể cả \t \n!=simplified()

    str = "Vladivostok";
    str.truncate(4);
    str+=str;
    // str == "VladVlad" cái này ngc lại là lấy, nếu ngoài chuỗi thì k xảy ra j, nếu âm thì coi là =0

    if (str[0] == QChar('?'))
        str[0] = QChar('_');
    //clear();isNull();isEmpty();fromUtf8();back();capacity();at();push_back();push_front();;toLocal8Bit();
    //toUtf8();toLatin1();unicode();setUnicode();
    //unicode ở đây là const QChar*; latin1 là 1 loại mã hóa unicode < UTF8;
    //toLatin1(),toUtf8() và toLocal8Bit() đều trả về QByteArray nhưng kiểu mã hóa nó khác nhau=>lấy,chuyển QByteArray or const char*

    QRegExp regexp("\\d+");
//    QRegExpValidator *rxValidator=new QRegExpValidator(regexp);
//    QValidator *validator=rxValidator;
//    ui->lineEdit->setValidator(rxValidator);
    QIntValidator *intval=new QIntValidator(0,100);
    ui->lineEdit->setText("5");
    QString str100=ui->lineEdit->text();
    int from=0;
    intval->validate(str100,from);//mẹ trong qt lúc thì truyền QString đc lúc thì k=> khi k thì phải làm như này
    //khi muốn lấy gt return thì dùng validate->đối số của nó phải là biến cụ thể chứ k đc truyền gt trực tiếp. Nguyên nhân:
//khi là int thì k đc truyền số như ta đã biết với c++, truyền tham trị or truyền con trỏ thì ko đc cho số vì nó sẽ refer
//đến địa chỉ chứa nó mà truyền số thì là 1 gt k địa chỉ(kiểu như để vào trong hàm nó nó đổi giá trị đó chẳng hạn thì phải
//là biến chứ). Còn với QString khi ta dùng & truyền tham trị thì rõ ràng k thể truyền TT ui->lineEdit->text();=> bản chất
//nằm ở kiến thức về rvalue và lvalue
//dùng lvalue reference k nhất thiết chỉ reference đến lvalue=> chỉ đúng khi truyền địa chỉ rvalue là đối tượng tạm bị xóa
//ngay. Nếu ta dùng đôi số copy VD int a; thì truyền vào số int bth vẫn đc
}

MainWindow::~MainWindow()
{
    delete ui;
}

