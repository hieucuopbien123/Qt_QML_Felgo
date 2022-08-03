#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void testFinished();
    void State(qint64,qint64);
    void showSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void showReplyErrors(QNetworkReply::NetworkError error);
private:
    Ui::Widget *ui;
    QNetworkAccessManager* manager;
    QString target;
};
#endif // WIDGET_H
