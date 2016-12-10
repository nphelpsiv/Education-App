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

void ContactListener::handleGroundContact(Ball* b) {
    b->remove();
}
