#include "contactlistener.h"

ContactListener::ContactListener()
{

}
void ContactListener::BeginContact(b2Contact *contact)
{
    void* objA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* objB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (objA && objB)
    {
        if(static_cast<Tower*>(objA) != 0)
            handleTowerContact(static_cast<Ball*>(objB),static_cast<Tower*>(objA));
        else if(static_cast<Ball*>(objA) != NULL)
            handleBallContact(static_cast<Ball*>(objB),static_cast<Ball*>(objA));
        else
            handleGroundContact(static_cast<Ball*>(objB));
    }
}

void ContactListener::EndContact(b2Contact *contact)
{

}

void ContactListener::handleTowerContact(Ball* b, Tower* t2)
{
    b->remove();
    t2->wasHit();
}

void ContactListener::handleBallContact(Ball* b1, Ball* b2) {
    b1->remove();
    b2->remove();
}

void ContactListener::handleGroundContact(Ball* b) {
    b->remove();
}
