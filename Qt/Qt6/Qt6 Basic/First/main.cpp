#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QVector<int> vectorVar(10,5);//vector qt6 là alias của QList mà thôi
    for(qsizetype i = 0; i < vectorVar.size(); ++i)
        qInfo() << vectorVar.at(i);
    qInfo() << Qt::endl;
    //QInfo, QDebug nó tự động xuống dòng sau khi in xong 1 dòng. Có thể dùng iostream cout nếu muôn


    return a.exec();
}
