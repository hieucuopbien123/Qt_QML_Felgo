#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    fileName = "test.xml";

    loadContent();

    ui->treeView->setModel(model);
}

Dialog::~Dialog()
{
    saveContent();//ta tạo ra 1 hàm gọi nh nơi tốt hơn vì chỉnh 1 phát là xong hơn là tạo nhiều version khác nhau of 1 hàm
    delete ui;
}

void Dialog::loadContent()
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open file for reading";
        return;
    }
    qDebug() << "Start reading";
    QDomDocument document;
    document.setContent(&file);
    file.close();

    QDomElement rootElement = document.firstChildElement("Books");
    QStandardItem* rootItem = new QStandardItem("Books");//ta sẽ fix root, k để user sửa root
    model->appendRow(rootItem);

    QDomNodeList listOfRoot = rootElement.elementsByTagName("Book");
    for(int i = 0; i < listOfRoot.count() ; i++)
    {
        QDomElement bookElement = listOfRoot.at(i).toElement();
        QStandardItem* bookItem = new QStandardItem(bookElement.attribute("Name"));
        rootItem->appendRow(bookItem);

        QDomNodeList listOfBook = bookElement.elementsByTagName("Chapter");
        for(int j = 0; j < listOfBook.count(); j++)
        {
            QDomElement chapterElement = listOfBook.at(j).toElement();
            bookItem->appendRow(new QStandardItem(chapterElement.attribute("Name")));
            //chỉ thêm kiểu QStandardItem thôi
        }
    }
    qDebug() << "Finish reading";
}

void Dialog::saveContent()
{
    qDebug() << "Start saving";
    QDomDocument document;
    QDomElement rootElement = document.createElement("Books");
    document.appendChild(rootElement);

    QStandardItem* rootItem = model->item(0,0);
    //hàm item của model lấy ra QStandardItem còn data chung lấy ra QVariant,nếu ta cần lấy các nhánh con thì cần lấy QStandardItem
    for(int i = 0; i < rootItem->rowCount(); i++)
    {
        QStandardItem* bookItem = rootItem->child(i,0);//item lấy của mẹ, child lấy từ con ra
        QDomElement bookElement = document.createElement("Book");
        bookElement.setAttribute("ID",i);
        bookElement.setAttribute("Name",bookItem->text());
        rootElement.appendChild(bookElement);
        for(int j = 0; j < bookItem->rowCount(); j++)
        {
            QStandardItem* chapterItem = bookItem->child(j);
            QDomElement chapterElement = document.createElement("Chapter");
            chapterElement.setAttribute("ID",j);
            chapterElement.setAttribute("Name",chapterItem->text());
            bookElement.appendChild(chapterElement);
        }
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file for writing";
    }
    QTextStream stream(&file);
    stream << document.toString();
    file.close();
    qDebug() << "Finish saving";
    //có thể dùng xml tạo và lưu lại danh sách vào file xml làm cơ sở dữ liệu
}
