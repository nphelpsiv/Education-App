#ifndef TOWER_H
#define TOWER_H

#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>

class Tower : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Tower();

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // TOWER_H
