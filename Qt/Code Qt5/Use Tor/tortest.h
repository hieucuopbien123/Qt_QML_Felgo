#ifndef TORTEST_H
#define TORTEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QNetworkProxy>

class TorTest : public QObject
{
    Q_OBJECT
public:
    explicit TorTest(QObject *parent = nullptr);

public slots:
    void getUrl();
    void replyFinished(QNetworkReply* reply);
private:
    QNetworkAccessManager* manager;
};

#endif // USETOR_H
