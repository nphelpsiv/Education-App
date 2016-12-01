#include "debris.h"

Debris::Debris(int x, int y, int r, b2World* worldb2)
{
    xPosD = x;
    yPosD = y;
    radD = r;
    world = worldb2;

    createDebrisBox2D();

    value = (rand() % 10) + 1;


}
Debris::~Debris()
{
    body->GetWorld()->DestroyBody(body);
}
QRectF Debris::boundingRect() const
{
     return QRectF(0,0,radD+4,radD+4);
}

void Debris::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(2, 2, radD, radD);
    painter->setPen(Qt::red);
}

void Debris::createDebrisBox2D()
{
    //Debris Position
    b2BodyDef debrisBodyDef;
    debrisBodyDef.type = b2_dynamicBody;
    debrisBodyDef.position.Set(xPosD, yPosD);
    debrisBodyDef.awake = true;
    body = world->CreateBody(&debrisBodyDef);
    body->SetUserData(this);

    //Debris Shape
    b2CircleShape debrisShape;
    debrisShape.m_radius = radD;


    //Debris Fixture
    b2FixtureDef debrisFixtureDef;
    debrisFixtureDef.shape = &debrisShape;
    debrisFixtureDef.density = .1f;
    debrisFixtureDef.friction = 0;
    debrisFixtureDef.restitution = 0.6f;
    body->CreateFixture(&debrisFixtureDef);

    //std::cout << "Will Apply Force" << std::endl;
    //Apply a force
    //body->ApplyForce(b2Vec2(2000.0f, 2000.0f), b2Vec2(10.0, 10.0f), false);
    body->ApplyLinearImpulseToCenter(b2Vec2(-xPosD*2000.0f, yPosD*1000.0f),true);
}
void Debris::move()
{
    //std::cout << "X position " << body->GetPosition().x << std::endl;
    //std::cout << "Y position " << body->GetPosition().y << std::endl;
    setPos(body->GetPosition().x, -body->GetPosition().y);
}
