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
}

void Debris::createDebrisBox2D()
{
    // Have a timer so that it can be destroyed after a little bit.
    timer = new QTimer(this);
    int randTime = rand() % 1000 + 250;
    timer->start(randTime);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(deleteDebrisParticle()));

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
    body->ApplyLinearImpulseToCenter(b2Vec2(xPosD*randX, yPosD*randY),true);
}

void Debris::move()
{
    setPos(body->GetPosition().x, -body->GetPosition().y);
}

void Debris::deleteDebrisParticle()
{
    emit deleteParticle();
    std::cout << "From Debris emitting delete particle" << std::endl;
}
