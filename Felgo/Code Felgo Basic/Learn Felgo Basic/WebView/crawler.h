#ifndef CRAWLER_H
#define CRAWLER_H

#include <QApplication>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Crawler: public QObject
{
     Q_OBJECT
public:
    explicit Crawler(QObject *parent = nullptr);

    Q_INVOKABLE void requestToWebsite(QString url);
    Q_INVOKABLE void getContentOfId(QString id);
};

#endif // CRAWLER_H
