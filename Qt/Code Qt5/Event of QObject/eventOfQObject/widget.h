#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
        bool event(QEvent* ev) override
        {
            if (ev->type() == QEvent::KeyPress)
            {
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(ev);
                qDebug() << "Ate key press 1" << keyEvent->key();
                return true;
            }
            else if(ev->type() == QEvent::Show)
            {
                QWidget::event(ev);
                return true;
            }
            return QWidget::event(ev);
        }
        void timerEvent(QTimerEvent *event);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
