#include "httpserver.h"

HttpServer::HttpServer(QObject *parent) : TcpServer(parent)
{
    m_root = QCoreApplication::applicationDirPath();//mặc định
    m_rate = 15360;
}

HttpServer::~HttpServer()
{

}

QString HttpServer::root()
{
    return m_root;
}

void HttpServer::setRoot(QString path)
{
    m_root = path;
    if(m_root.endsWith("/") || m_root.endsWith("\\"))
    {//bất cứ khi nào thao tác với link đều phải kiểm tra các dạng của link file
        m_root = m_root.mid(0, m_root.length() - 1);
    }
    qDebug() << this << "root set to:" << m_root;
}

int HttpServer::rate()
{
    return m_rate;
}

void HttpServer::setRate(int value)
{
    m_rate = value;
    qDebug() << this << "rate set to:" << value;
}

void HttpServer::incomingConnection(qintptr descriptor)
{//reimplement ở đây thì dùng cái này sẽ thế hoàn toàn incoming ở class cha
    qDebug() << this << "Incomming HTTP connection: " << descriptor;

    HttpConnection *connection = new HttpConnection();
    connection->setRate(m_rate);
    connection->setRoot(m_root);
    accept(descriptor,connection);
}
//Khi dùng như này thì, biến connections vẫn có trong server lưu dưới dạng TcpConnection, tất nhiên thực tế ta lưu là
//HttpConnection nên cast sang dùng lúc nào cx đc. Do các hàm k có gì thay đổi nên k sửa gì thêm.
