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
        handleContact(static_cast<Ball*>(objB),static_cast<Tower*>(objA));
    }

}

void ContactListener::EndContact(b2Contact *contact)
{

}

void ContactListener::handleContact(Ball* b, Tower* t2) {
    b->remove();
    std::cout << "hit" << std::endl;
    t2->wasHit();
}
