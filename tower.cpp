#include "tower.h"

Tower::Tower(int x, int y, int w, int h, b2World* worldb2)
{
    xPos = x;
    yPos = y;
    width = w;
    height = h;
    world = worldb2;

    createTowerBox2D();
}

Tower::~Tower()
{

}

QRectF Tower::boundingRect() const
{
     return QRectF(0,0,50,10);
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

void Tower::createTowerBox2D()
{
    //Tower Position
    b2BodyDef towerBodyDef;
    towerBodyDef.type = b2_staticBody;
    towerBodyDef.position.Set(xPos, yPos);
    b2Body* towerBody = world->CreateBody(&towerBodyDef);

    //Tower Shape
    b2PolygonShape towerShape;
    towerShape.SetAsBox(width, height);

    //Tower Fixture
    b2FixtureDef towerFixtureDef;
    towerFixtureDef.shape = &towerShape;
    towerFixtureDef.density = 1;
    towerBody->CreateFixture(&towerFixtureDef);
}
