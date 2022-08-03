#include "tortest.h"

TorTest::TorTest(QObject *parent) : QObject(parent)
{

}

void TorTest::getUrl()
{
    //QNetworkProxy cung 1 tầng network proxy(vì cái proxy server là cầu nối giữa ng dùng và internet đã biết đó)
    //cụ thể nó cung các method để ta tùy chỉnh networklayer proxy support cho các class network qt khác, vd: nó
    //support QAbstractSocket, QNetworkAccessManager,.. Như v ta vào mạng bằng app thông qua cái proxy này
    QNetworkProxy proxy;//tạo. Proxy nào cx có type, host name,port hoạt động, ta có thể set password nếu muốn
    proxy.setType(QNetworkProxy::DefaultProxy);
    proxy.setHostName("tor-exit-relay-8.anonymizing-proxy.digitalcourage.de");
    proxy.setPort(9150);
//    proxy.setUser("username");
//    proxy.setPassword("password");
    QNetworkProxy::setApplicationProxy(proxy);

    qDebug() << "Connecting...";
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("https://whatismyip.host/")));
}

void TorTest::replyFinished(QNetworkReply *reply)
{
    qDebug() << "Response...";
    if(reply->isOpen())//kiểm tra khá là thừa vì mới quet xong nó kiểu gì chả mở
    {
        qDebug() << reply->read(10000);
        reply->close();
    }
}
