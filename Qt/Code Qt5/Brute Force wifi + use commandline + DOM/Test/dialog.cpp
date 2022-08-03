#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    password[8] = '\0';
    password[7] = '1';
    password[6] = '9';
    password[5] = '9';
    password[4] = '1';
    password[3] = '3';
    password[2] = '0';
    password[1] = '6';
    isQuit = 0;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
//    QFuture<void> test = QtConcurrent::run((this),&Dialog::checkLoop);
    int re = run(0);
    qDebug() << "re: " << re;
}

int Dialog::run(int index)
{
    for(int i = 0; i < 8; i++)
    {
        if(isQuit == 1)
        {
            break;
        }
        password[index] = i + '0';
        qDebug() << "index: " << index;
        if(index == 0)
        {
            qDebug() << "Pass: " << password;
            QDomDocument dom;
            QFile file("wifi.xml");
            if(!file.open(QFile::ReadOnly))
            {
                qDebug() << "Cannot open file to read";
            }
            dom.setContent(&file);
            file.close();

            QDomElement root = dom.documentElement();
            QDomElement child = root.firstChildElement();
            QDomElement newNodeTag = dom.createElement("name");
            QDomText newText = dom.createTextNode(ui->lineEdit->text());
            newNodeTag.appendChild(newText);
            root.replaceChild(newNodeTag, child);

            QDomElement temp = newNodeTag.nextSibling().toElement();
            QDomElement child1 = temp.firstChildElement();
            QDomElement child2 = child1.firstChildElement();
            QDomElement newNodeTag2 = dom.createElement("name");
            QDomText newText2 = dom.createTextNode(ui->lineEdit->text());
            newNodeTag2.appendChild(newText2);
            child1.replaceChild(newNodeTag2, child2);

            QDomElement final = root.elementsByTagName("MSM").at(0).toElement();
            QDomElement security = final.firstChildElement();
            QDomElement sharedKey = security.elementsByTagName("sharedKey").at(0).toElement();
            QDomElement keyMaterial = sharedKey.elementsByTagName("keyMaterial").at(0).toElement();
            QDomElement newNodeTag3 = dom.createElement("keyMaterial");
            QDomText newText3 = dom.createTextNode(password);
            newNodeTag3.appendChild(newText3);
            sharedKey.replaceChild(newNodeTag3, keyMaterial);//code như js v

            QFile file2("wifi.xml");
            if(!file2.open(QFile::WriteOnly))
            {
                qDebug() << "Cannot open file to write";
            }
            QTextStream stream(&file2);
            stream << dom.toString();
            file2.close();
            QProcess process;
            if(isQuit == 1)
            {
                break;
            }

//            process.start("netsh wlan add profile filename=\"B:/Qt/newGeneration/build-Test-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/wifi.xml\"");
//            process.waitForFinished(-1);
//            process.start("netsh wlan connect ssid=" + ui->lineEdit->text() + " name=" + ui->lineEdit->text());
//            process.waitForFinished(-1);
//            process.start("timeout\t3");
//            process.waitForFinished(-1);
//            process.start("netsh interface show interface");
//            process.waitForFinished(-1);
//            process.start("date");
//            process.waitForFinished(-1);

            system("netsh wlan add profile filename=\"B:/Qt/newGeneration/build-Test-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/wifi.xml\"");
            system(("netsh wlan connect ssid=" + ui->lineEdit->text() + " name=" + ui->lineEdit->text()).toLocal8Bit().data());
            system("timeout\t4");
            system(("netsh interface show interface name=\"Wi-Fi 2\">test.txt"));

            QFile xmlFile1;
            QFile file3("test.txt");
            if(!file3.open(QFile::ReadOnly))
            {
                qDebug() << "Cannot open file to write";
            }
            QTextStream stream2(&file3);
            QString check = stream2.readAll();
            qDebug() << check;
            file2.close();
                      if(check.contains("Connected"))
                      {
                          qDebug() << "You are connected!";
                          return 100;
                      }

//            QByteArray check = process.readAllStandardOutput();
//            if(check.contains("Connected"))
//            {
//                qDebug() << "Found it!";
//                return 100;
//            }
        }
        else
        {
            int re = run(index + 1);
            if(re == 100)
                return re;
        }
    }
}

char* Dialog::checkLoop()
{
    while(check() != 1 && isQuit == 0);
    QReadWriteLock lock;
    lock.lockForWrite();
    isQuit = 1;
    lock.unlock();
    qDebug() << "Finish";
}

int Dialog::check()
{
    QProcess processCheck;
    processCheck.start("netsh interface show interface");
    processCheck.waitForFinished(-1);
    QByteArray check = processCheck.readAllStandardOutput();
    if(check.contains("Connected"))
        return 1;
    else
        return 0;
}

void Dialog::on_pushButton_2_clicked()
{
    QReadWriteLock lock;
    lock.lockForWrite();
    isQuit = 1;
    lock.unlock();
}
