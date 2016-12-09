#include "ground.h"

Ground::Ground(int x, int y, int w, int h, b2World* worldb2)
{
    xPos = x;
    yPos = y;
    width = w;
    height = h;
    world = worldb2;

    createGroundBox2D();
}

Ground::~Ground()
{
    world->DestroyBody(groundBody);
}

void Ground::createGroundBox2D()
{
    //Ground position
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(xPos, yPos);
    groundBody = world->CreateBody(&groundBodyDef);
    groundBody->SetUserData(this);

    //Ground Shape
    b2PolygonShape groundShape;
    groundShape.SetAsBox(width, height);

    //Ground Fixture
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundFixtureDef.density = 1;
    groundBody->CreateFixture(&groundFixtureDef);
}


QPoint Ground::getPosition()
{
    return QPoint(groundBody->GetPosition().x * 0.6, -groundBody->GetPosition().y * 0.6);
}
