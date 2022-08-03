#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QPainter>
#include <QGraphicsScene>

class MyItem : public QGraphicsItem
{
public:
    MyItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void advance(int phase) override;

private:
    qreal speed;
    void DoCollision();
    QRandomGenerator* ranEngine;
};

#endif // MYITEM_H
