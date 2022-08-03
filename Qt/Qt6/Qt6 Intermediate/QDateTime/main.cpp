#include <QCoreApplication>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <QTimeZone>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDate today = QDate::currentDate();
    qInfo() << today.day() << " " << today.dayOfYear();
    qInfo() << today.daysTo(today.addDays(45));
    qInfo() << today;
    qInfo() << today.addDays(1);
    qInfo() << today.addYears(20);

    qInfo() << "\nChange Format: ";
    qInfo() << "ISODate" << today.toString(Qt::DateFormat::ISODate);
    qInfo() << "RFC2822Date" << today.toString(Qt::DateFormat::RFC2822Date);
    qInfo() << "TextDate" << today.toString(Qt::DateFormat::TextDate) << "\n";

    QTime now = QTime::currentTime();
    Q_UNUSED(now.addSecs(2));
    qInfo() << now.toString(Qt::DateFormat::TextDate);
    qInfo() << now.msec();
    qInfo() << QTime(24,12,0).isValid();

    QDateTime current = QDateTime::currentDateTime();
    Q_UNUSED(current.addSecs(2));
    Q_UNUSED(current.addMonths(2));
    qInfo() << current.timeZone();
    qInfo() << current.time();
    qInfo() << "Normal: " << current;

    qInfo() << "Custom format: " << current.toString("ddd MMM d yy hh:mm:ss.zzz");
    qInfo() << "To UTC: " << current.toUTC();
    //d và dd là ngày số;ddd là thứ;MM là tháng số và MMM/MMMM là tháng chữ;yy và yyyy là năm số->tùy biến định dạng dài ngắn

    QDateTime expire = current.addDays(45);
    qInfo() << "Expired on" << expire;
    if(current > expire)
    {
        qInfo() << "Expired!!";
    }
    else
    {
        qInfo() << "Not expired!";
    }

    return a.exec();
}
