#include <QCoreApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QString serverName="DESKTOP-GN3V8MM\\SQLEXPRESS";
//    QString dbName="Test";
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    qDebug() << QSqlDatabase::isDriverAvailable("QODBC");

//    db.setConnectOptions();
//    QString dsn=QString("DRIVER={SQL Server Native Client 11.0};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(serverName).arg(dbName);
//    db.setDatabaseName(dsn);

    db.setHostName("DESKTOP-GN3V8MM\\SQLEXPRESS");
    db.setDatabaseName("mydsn32");

    if(db.open())
    {
        qDebug() << "Opened!";

        QSqlQuery qry;
        if(qry.exec("SELECT * FROM [Test].[dbo].[Table1]"))//thực hiện và lưu các kết quả vào biến qry(như 1 list)
        {
             while(qry.next()){
                 qDebug() << qry.value(0).toString() << qry.value(1).toString();
             }
        }else{
            qDebug() << "Error: " << db.lastError().text();
        }

        //trong sql còn có thể prepare và bind. Khi prepare thì query đc chuẩn bị sẵn, r, muôn thực hiện vs các value khác nhau
        //thì bindValueu để thể vào là xong.
        QSqlQuery qry2;
        QString strQuery2="INSERT INTO [Test].[dbo].[Table1]([Name],[Age]) VALUES(:name,:age)";
        qry2.prepare(strQuery2);
        qry2.bindValue(":first","Trang");
        qry2.bindValue(":age","100");
        // dùng : để thay thế QVariant
        if(qry2.exec())
        {
            qDebug() << "Qry2 is executed";
        }

        db.close();//xóa kết nối, vô hiệu hóa query,...
    }
    else
    {
        qDebug() << db.lastError().text();//có hẳn lớp QSqlError để lo lỗi
    }

    return a.exec();
}
