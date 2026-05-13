
#pragma once
#include "DynamicObject.h"
#include "box2d/box2d.h"
#include <iostream>
#include <list>
#include <set>
/// \brief Custom contact listener to handle collision events in Box2D. Overrides the default contact listener to provide custom behaviour when collisions occur.

class ContactListener : public b2ContactListener {

    public:
        std::set<uintptr_t> s_ptr;
       
        ContactListener() = default;

    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact) override
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        uintptr_t idA = fixtureA->GetBody()->GetUserData().pointer;
        uintptr_t idB = fixtureB->GetBody()->GetUserData().pointer;

        // Bird A hit Pig B — store pig's ID
        if (idA == 100 && idB > 0 && idB < 10)
        {
            s_ptr.insert(idB); // pig ID
            std::cout << "Bird hit Pig " << idB << std::endl;
        }

        // Bird B hit Pig A — store pig's ID
        if (idB == 100 && idA > 0 && idA < 10)
        {
            s_ptr.insert(idA); // pig ID
            std::cout << "Bird hit Pig " << idA << std::endl;
        }
    }

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact) override {
       // std::cout << "Collision Ended" << std::endl;
    }

    std::set<uintptr_t> getPointer() {
        return s_ptr;
    }

    void clearPointers()
    {
        s_ptr.clear();
    }

};