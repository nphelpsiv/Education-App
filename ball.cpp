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

    value = (rand() % 10) + 1;
}

Ball::~Ball()
{
    body->GetWorld()->DestroyBody(body);
}

/*QRectF Ball::boundingRect() const
{
     return QRectF(0,0,rad+4,rad+4);
}*/

/*void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(2, 2, rad, rad);
    painter->setPen(Qt::red);
    painter->setFont(QFont("Arial", 20, QFont::Bold));
    painter->drawText(8, 25, QString::number(value));
}*/

/*void Ball::timerEvent(QTimerEvent *event)
{

}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}*/

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

    //std::cout << "Will Apply Force" << std::endl;
    //Apply a force
    //body->ApplyForce(b2Vec2(2000.0f, 2000.0f), b2Vec2(10.0, 10.0f), false);
    body->ApplyLinearImpulseToCenter(b2Vec2(-xPos*2000.0f, yPos*1000.0f),true);
}

/*void Ball::move()
{
    //std::cout << "X position " << body->GetPosition().x << std::endl;
    //std::cout << "Y position " << body->GetPosition().y << std::endl;
    setPos(body->GetPosition().x, -body->GetPosition().y);
}*/

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

QPoint Ball::getPosition()
{
    return QPoint(body->GetPosition().x * 0.6, -body->GetPosition().y * 0.6);
}
