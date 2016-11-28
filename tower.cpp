#include "tower.h"

Tower::Tower(int x, int y, int w, int h, b2World* world)
{
    xPos = x;
    yPos = y;
    width = w;
    height = h;

    //Tower Position
    b2BodyDef towerBodyDef;
    towerBodyDef.type = b2_staticBody;
    towerBodyDef.position.Set(0, -5);
    b2Body* towerBody = world->CreateBody(&towerBodyDef);

    //Tower Shape
    b2PolygonShape towerShape;
    towerShape.SetAsBox(3, 7);

    //Tower Fixture
    b2FixtureDef towerFixtureDef;
    towerFixtureDef.shape = &towerShape;
    towerFixtureDef.density = 1;
    towerBody->CreateFixture(&towerFixtureDef);


}

Tower::~Tower()
{

}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(xPos, yPos, width, height);
}

void Tower::timerEvent(QTimerEvent *event)
{

}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

QRectF Tower::boundingRect() const
{
     return QRectF(0,0,50,10);
}
