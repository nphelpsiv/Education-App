#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#include <Box2D/Box2D.h>
#include <iostream>
#include "ball.h"
#include "tower.h"
#include "ground.h"


class ContactListener : public b2ContactListener
{
public:
    ContactListener();
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void handleTowerContact(Ball* b, Tower* t);
    void handleGroundContact(Ball* b);

private:
    bool contactMade;

    b2Fixture* GetFixtureA();
    b2Fixture* GetFixtureB();
};

#endif // CONTACTLISTENER_H
