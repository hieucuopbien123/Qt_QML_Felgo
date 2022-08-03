#include <QCoreApplication>
#include <QtXml>

void showElementOf(QDomElement rootElement, QString tagName, QString attributeOfTagNameToShow)
{
    QDomNodeList nodeList = rootElement.elementsByTagName(tagName);

    for(int i = 0; i < nodeList.count(); i++)//như ta đã biết nên dùng foreach
    {
        QDomNode node = nodeList.at(i);
        //Cái node có thể là mọi các cục trong xml còn element trong xml là từng thẻ riêng biệt
        //ta chuyển qua node r chuyển qua element sau
        if(node.isElement())
        {
            QDomElement element = node.toElement();
            qDebug() << element.attribute(attributeOfTagNameToShow);
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDomDocument document;//là cả 1 document lớn trong XML, bên trong document này có các thẻ element. Tạo
    //như này là bên trong nó trống chỉ có dòng declaration. Biến này lưu r nhưng k thấy, ta phải lưu vào file để xem
    QDomElement root = document.createElement("Books");//root là ! nhưng có nh con, mỗi con lại có nh element con
    //createElement tạo element từ document có thể add đc vào document
    document.appendChild(root);
    for(int i = 0; i < 10; i++)
    {
        QDomElement book = document.createElement("Book");
        book.setAttribute("Name", "My book " + QString::number(i));//muốn từng thẻ là gì xml ta phải tự báo tên thẻ
        book.setAttribute("ID", QString::number(i));
        root.appendChild(book);//luôn dùng document để create và cái element đó dùng trong phạm vi document đó
        //ta có thể add nó vào trong root or 1 ele đều ok
        for(int j = 0; j < 10; j++)
        {
            QDomElement chapter = document.createElement("Chapter");
            //cái Chapter gọi là tagname,còn Name vs ID là attribute của element có tagname đó
            chapter.setAttribute("Name", "My chapter " + QString::number(j));
            chapter.setAttribute("ID", QString::number(j));
            book.appendChild(chapter);
        }
    }
    QFile file("test.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug("Cannot open");
        return -1;
    }
    else
    {
        QTextStream stream(&file);
        stream << document.toString();//document bh lưu toàn bộ dữ liệu file xml của ta, chuyển đc sang string
        file.close();
        qDebug("Finished writing");
    }
    //tạo document->tạo element->đặt thuộc tính cho element->add element vào document->chuyển document sang string->file

    //Reading XML file
    QDomDocument rDocument;
    QFile rFile("test.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file";
        return -1;
    }
    rDocument.setContent(&rFile);//or string hay bytearray đều ok
    file.close();

    QDomElement rootElement = rDocument.firstChildElement();//vì root có ! và ở đầu
    showElementOf(rootElement,"Book","Name");

    //cách hiển thị.Lấy cái element cần hiển thị nội dung bên trong ra, ta lấy danh sách các thành phần bên trong đó
    //bằng tagname (chuyển sang node r từ node sang element)->thế là có element, in attribute của nó là xong
    QDomNodeList nodeListOfBook = rootElement.elementsByTagName("Book");
    for(int i = 0; i < nodeListOfBook.count(); i++)
    {
        QDomNode node = nodeListOfBook.at(i);
        if(node.isElement())
        {
            QDomElement eachBookElement = node.toElement();
            qDebug() << "Show element of: " << eachBookElement.attribute("Name");
            showElementOf(eachBookElement,"Chapter","Name");
        }//cần bình tĩnh phân biệt rõ thuộc tính element và các thuộc tính bên trong nó
    }
    //for each cx chỉ dùng đc vs 1 vài dạng list, nếu k dùng đc thì chuyển qua for bth

    qDebug() << "Finish Reading";
    //dùng DOM khi read thì nó sẽ đọc toàn bộ cái XML r ms xem ta thích in gì ra thì in, có nhiều loại tool khác cho
    //ta chỉ lấy cái cần đọc

    return a.exec();
}
