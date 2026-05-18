
#pragma once
#include "DynamicObject.h"
#include "box2d/box2d.h"
#include <iostream>
#include <list>
#include <set>
#include <map>

/// \brief Custom contact listener to handle collision events in Box2D. Overrides the default contact listener to provide custom behaviour when collisions occur.

class ContactListener : public b2ContactListener {

    public:
        std::set<uintptr_t> s_ptr;
        std::multimap<b2Fixture*, b2Fixture*> mm_contactPairs;
        std::set<b2Body*> s_destructionQueue;
       
        ContactListener() = default;

    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact) override
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        // Store both directions (A hit B and B hit A)
        mm_contactPairs.insert({fixtureA, fixtureB});
        mm_contactPairs.insert({fixtureB, fixtureA});

        uintptr_t idA = fixtureA->GetBody()->GetUserData().pointer;
        uintptr_t idB = fixtureB->GetBody()->GetUserData().pointer;

        // Bird A hit Pig B — store pig's ID
        if (idA == 100 && idB > 0 && idB < 10)
        {
            // s_ptr.insert(idB); // pig ID
            s_destructionQueue.insert(fixtureB->GetBody());
            std::cout << "Bird hit Pig " << idB << std::endl << "Pig " << idB << " added to destruction queue" << std::endl;
        }

        // Bird B hit Pig A — store pig's ID
        if (idB == 100 && idA > 0 && idA < 10)
        {
            // s_ptr.insert(idA); // pig ID
            s_destructionQueue.insert(fixtureA->GetBody());
            std::cout << "Bird hit Pig " << idA << std::endl << "Pig " << idA << " added to destruction queue" << std::endl;
        }
    }

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact) override
    {
       // std::cout << "Collision Ended" << std::endl;
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        // Remove contact pair when objects stop touching
        auto range = mm_contactPairs.equal_range(fixtureA);

        // A hit B
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second == fixtureB)
            {
                mm_contactPairs.erase(it);
                break;
            }
        }

        // Remove reverse pair B hit A 
        auto range2 = mm_contactPairs.equal_range(fixtureB);

        for (auto it = range2.first; it != range2.second; ++it)
        {
            if (it->second == fixtureA)
            {
                mm_contactPairs.erase(it);
                break;
            }
        }
    }

    std::pair<std::multimap<b2Fixture*, b2Fixture*>::iterator, std::multimap<b2Fixture*, b2Fixture*>::iterator>findContacts(b2Fixture* fixture)
    {
        return mm_contactPairs.equal_range(fixture);
    }

    std::set<uintptr_t> getPointer()
    {
        return s_ptr;
    }

    void clearPointers()
    {
        s_ptr.clear();
    }

};