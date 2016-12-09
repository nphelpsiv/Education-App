#include "tower.h"

Tower::Tower(int x, int y, int w, int h, b2World* worldb2)
{
    xPos = x;
    yPos = y;
    width = w;
    height = h;
    world = worldb2;
    isDestroyed = false;
    collided = false;

    health = 100;

    createTowerBox2D();

    textureIndex = 0;
}

Tower::~Tower()
{
    world->DestroyBody(towerBody);
}

void Tower::createTowerBox2D()
{
    //Tower Position
    b2BodyDef towerBodyDef;
    towerBodyDef.type = b2_staticBody;
    towerBodyDef.position.Set(xPos, yPos);
    towerBody = world->CreateBody(&towerBodyDef);

    towerBody->SetUserData(this);

    //Tower Shape
    b2PolygonShape towerShape;
    towerShape.SetAsBox(width, height);

    //Tower Fixture
    b2FixtureDef towerFixtureDef;
    towerFixtureDef.shape = &towerShape;
    towerFixtureDef.density = 1;
    towerBody->CreateFixture(&towerFixtureDef);
}

void Tower::wasHit()
{
    health -= 10;

    if (health <= 0)
    {
        isDestroyed = true;
    }
    emit healthChanged(health);

    collided = true;
}
bool Tower::destroyed()
{
    return isDestroyed;
}

bool Tower::hasCollided()
{
    bool temp = collided;
    collided = false;
    return temp;
}

void Tower::setHealth(int h)
{
    health = h;
}
int Tower::getHealth()
{
    return health;
}

QPoint Tower::getPosition()
{
    return QPoint(towerBody->GetPosition().x * 0.6, -towerBody->GetPosition().y * 0.6);
}
