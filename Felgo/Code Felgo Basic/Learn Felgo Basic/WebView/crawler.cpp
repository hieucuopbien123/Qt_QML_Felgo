#include "crawler.h"

Crawler::Crawler(QObject *parent) : QObject(parent)
{

}

void Crawler::requestToWebsite(QString url)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager,&QNetworkAccessManager::finished,this,[&](QNetworkReply* reply){
        QByteArray data = reply->readAll();
        QString str=QString::fromLatin1(data);
        qDebug() << str;
    });
    connect(manager, &QNetworkAccessManager::finished, manager, &QNetworkAccessManager::deleteLater);
}

void Crawler::getContentOfId(QString id)
{
    requestToWebsite("https://lovehands.vn/");
}
