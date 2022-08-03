#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QConicalGradient>
#include <QRadialGradient>
#include <QLinearGradient>
#include <QTextDocument>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

protected:
    void paintEvent(QPaintEvent* event);
    //hàm tự động phát khi: update,repaint đc gọi, khi màn đc set event này hiển thị ra ở bất cứ TH nào,khi có thay đổi,...
};
#endif // WIDGET_H
