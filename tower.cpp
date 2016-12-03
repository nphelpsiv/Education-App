#include "tower.h"

Tower::Tower(int x, int y, int w, int h, b2World* worldb2)
{
    xPos = x;
    yPos = y;
    width = w;
    height = h;
    world = worldb2;
    isDestroyed = false;

    health = 100;

    createTowerBox2D();
}

Tower::~Tower()
{

}

void Tower::createTowerBox2D()
{
    //Tower Position
    b2BodyDef towerBodyDef;
    towerBodyDef.type = b2_staticBody;
    towerBodyDef.position.Set(xPos, yPos);
    b2Body* towerBody = world->CreateBody(&towerBodyDef);

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

    //Each time this is called "red flash" sprite should be called for maybe 1/2 or 30 frames?

    if(health == 70)
    {
        //Change to slightly damaged sprite
    }
    else if(health == 40)
    {
        //Change to heavy damaged sprite
    }
    else if(health == 20)
    {
        //Change to ridiculous damaged sprite
    }
    if (health <= 0)
    {
        isDestroyed = true;
    }
    emit healthChanged(health);
}
bool Tower::destroyed()
{
    return isDestroyed;
}
