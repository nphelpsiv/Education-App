#include "tower.h"

Tower::Tower()
{
    QPainter *painter = new QPainter();
    QPen pen(Qt::red, 5);
    painter->setPen(pen);
    painter->drawRect(0, 0, 90, 60);

}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::red, 5);
    painter->setPen(pen);
    painter->drawRect(0, 0, 220, 300);
}

void Tower::timerEvent(QTimerEvent *event)
{

}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

QRectF Tower::boundingRect() const
{
     return QRectF(0,0,100,100);
}
