#include "ground.h"

Ground::Ground(int x, int y, int w, int h, b2World* worldb2)
{
    xPos = x;
    yPos = y;
    width = w;
    height = h;
    world = worldb2;
    isDestroyed = false;

    health = 100;

    createTowerBox2D();

    textureIndex = 0;
}

Ground::~Ground()
{
    world->DestroyBody(towerBody);
}

void Ground::createGroundBox2D()
{
    //Ground Position
    b2BodyDef towerBodyDef;
    towerBodyDef.type = b2_staticBody;
    towerBodyDef.position.Set(xPos, yPos);
    towerBody = world->CreateBody(&towerBodyDef);

    towerBody->SetUserData(this);

    //Ground Shape
    b2PolygonShape towerShape;
    towerShape.SetAsBox(width, height);

    //Ground Fixture
    b2FixtureDef towerFixtureDef;
    towerFixtureDef.shape = &towerShape;
    towerFixtureDef.density = 1;
    towerBody->CreateFixture(&towerFixtureDef);
}

void Ground::wasHit()
{
    health -= 10;

    if (health <= 0)
    {
        isDestroyed = true;
    }
    emit healthChanged(health);
}
bool Ground::destroyed()
{
    return isDestroyed;
}

void Ground::setHealth(int h)
{
    health = h;
}
int Ground::getHealth()
{
    return health;
}

QPoint Ground::getPosition()
{
    return QPoint(tower Body->GetPosition().x * 0.6, -towerBody->GetPosition().y * 0.6);
}
