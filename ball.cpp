#include "ball.h"

/*!
 * Create a new ball
 * with (xPosition, yPostion, radius, worldReference)
*/
Ball::Ball(int x, int y, int r, b2World* worldb2)
{
    xPos = x;
    yPos = y;
    rad = r;
    world = worldb2;

    createBallBox2D();

    collided = false;

    value = (rand() % 9) + 0;
}

Ball::~Ball()
{
    body->GetWorld()->DestroyBody(body);
}


void Ball::createBallBox2D()
{
    //Ball Position
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(xPos, yPos);
    ballBodyDef.awake = true;
    body = world->CreateBody(&ballBodyDef);
    body->SetUserData(this);

    //Ball Shape
    b2CircleShape ballShape;
    ballShape.m_radius = rad;

    //Ball Fixture
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = .1f;
    ballFixtureDef.friction = 0;
    ballFixtureDef.restitution = 0.6f;
    body->CreateFixture(&ballFixtureDef);

    //Apply a force
    body->ApplyLinearImpulseToCenter(b2Vec2(-xPos*(rand()%2000), yPos*(rand()%1000)),true);
}

//sets collided to true when it has collided with the tower.
void Ball::remove()
{
    collided = true;
}

bool Ball::hasCollided()
{
    return collided;
}

int Ball::getValue()
{
    return value;
}
int Ball::getX()
{
    return (int)body->GetPosition().x;
}
int Ball::getY()
{
    return -(int)body->GetPosition().y;
}

QPoint Ball::getPosition()
{
    return QPoint(body->GetPosition().x * 0.6, -body->GetPosition().y * 0.6);
}
