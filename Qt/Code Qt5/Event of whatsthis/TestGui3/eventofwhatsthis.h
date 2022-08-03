#ifndef EVENTOFWHATSTHIS_H
#define EVENTOFWHATSTHIS_H

#include <QObject>
#include <QWhatsThisClickedEvent>

class eventOfWhatsThis : public QObject
{
    Q_OBJECT
public:
    explicit eventOfWhatsThis(QObject *parent = nullptr);
signals:
    void linkClicked(const QString&);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if(event->type() == QEvent::WhatsThisClicked)
        {
            QWhatsThisClickedEvent* wtcEvent = static_cast<QWhatsThisClickedEvent*>(event);//static_cast có () nhé
            emit linkClicked(wtcEvent->href());//có hẳn 1 lớp QWhatsThisClickedEvent để quản lý event cho whatsthis
            return true;
        }
        return false;
    }
    //cơ chế:tất cả đều tương tự, khi thao tác vs thread ta cũng có slot tự động thì event cx v, nhưng mà thread ta đã có thể
    //biến bất cứ hàm nào cx thành thread đc do tính chất đặc biệt 4 hàm connect,slot bắt vs signal start sẽ đc thực hiện độc
    //lập. Còn event thì ta ms chỉ thực hiện độc lập chứ nếu muốn dùng các biến trong class ban đầu thì sao=> rất đơn giản, cho
    //cái event phát ra signal và để class bắt nó là đc.
    //ta có thể dùng cái QString của whatsthis là 1 TP của class r dùng cx đc nhưng ở đây có 1 class riêng bắt sự kiện của
    //whatsthis href nên ta dùng ntn cho chuẩn->thực chất QEvent type nó có hầu hết đầy đủ các loại sự kiện, ta nên KT trc r
    //hãng tự chế ra sự kiện

signals:

};

#endif // EVENTOFWHATSTHIS_H
