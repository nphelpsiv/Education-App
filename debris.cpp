#include "debris.h"

Debris::Debris(int x, int y, int r, b2World* worldb2)
{
    xPosD = x;
    yPosD = y;
    radD = r;
    world = worldb2;

    createDebrisBox2D();
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

    //Make it not collidable
    debrisFixtureDef.filter.categoryBits = 0;
    debrisFixtureDef.filter.groupIndex = 0;
    debrisFixtureDef.filter.maskBits = 0;

    body->CreateFixture(&debrisFixtureDef);

    // Give the debris a random direction to go.
    int randX = rand() % 15 + (-15);
    int randY = rand() % 70 + (-70);
    value = randX + randY;
    body->ApplyLinearImpulseToCenter(b2Vec2(xPosD*randX, yPosD*randY),true);
}

void Debris::move()
{
    setPos(body->GetPosition().x * 0.6, -body->GetPosition().y * 0.6);
}

// The value of this particle
// used for determining if particles are equal to each other
int Debris::getValue()
{
    return value;
}

QPoint Debris::getPosition()
{
    QPoint p(body->GetPosition().x*0.6, -body->GetPosition().y*0.6);
    return p;
}
