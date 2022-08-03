#ifndef MYSQUAREITEM_H
#define MYSQUAREITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPainter>

class mySquareItem : public QGraphicsItem
{
public:
    mySquareItem();
    //tự tạo hình cho riêng mình, chỉ cần reimplement của lớp QGraphicsItem các hàm CB cần thiết
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool pressed;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYSQUAREITEM_H
