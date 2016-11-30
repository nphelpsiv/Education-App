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
        handleContact(static_cast<Ball*>(objA),static_cast<Tower*>(objB));
    }

}
void ContactListener::EndContact(b2Contact *contact)
{

}
void ContactListener::handleContact(Ball* b, Tower* t2) {
    std::cout << "Hit" << std::endl;
}
