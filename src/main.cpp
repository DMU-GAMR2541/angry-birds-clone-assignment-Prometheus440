#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <list>

#include "Pig.h"
#include "Bird.h"
#include "Catapult.h"
#include "NonInteractable.h"
#include "ContactListener.h"

// Upcasting function
void listDynamics(DynamicObject* obj, std::string name)
{
    // Gets all types of dynamic objects and prints them out
    std::cout << name << " has been upcast" << std::endl;
}

int main() {
    /*
    *       VARIABLES
    */


    // === Input variables ===
	bool b_isDragging = false; // For mouse dragging
    bool b_birdFired = false; // To prevent sprites being deleted before any launch
    b2Vec2 b2_dragStartPos(0.0f, 0.0f); // To set birds start vector for relative launches


    // === Arrays ===
    std::string a_birdSpritePaths[3] = { "../assets/Ang_Birds/red.png", "../assets/Ang_Birds/yellow.png", "../assets/Ang_Birds/blue.png"};
    std::string a_pigSpritePaths[3] = { "../assets/Ang_Birds/pig.png", "../assets/Ang_Birds/pig_helmet.png", "../assets/Ang_Birds/pigKing.png"};

    float a_birdXPos[3] = {250.0f, 300.0f, 500.0f};
    float a_birdScales[3] = {0.025f, 0.075f, 0.065f};
    float a_pigXPos[3] = { 400.0f, 600.0f, 800.0f};
    float a_pigScales[3] = { 0.04f, 0.225f, 0.6f};


    // === Multimap ===
    std::multimap<std::string, std::unique_ptr<DynamicObject>> mm_dynamicObjects; //multimap, key is a string which looks for the type, the value is the unique pointer
    // Bird loop
    for (int i = 0; i < 3; i++)
    {
        mm_dynamicObjects.insert({"Bird", std::unique_ptr<DynamicObject>(new Bird(a_birdSpritePaths[i], a_birdXPos[i], 300.0f, a_birdScales[i]))});
    }
    // Pig loop
    for (int i = 0; i < 3; i++)
    {
        mm_dynamicObjects.insert({"Pig", std::unique_ptr<DynamicObject>(new Pig(1, a_pigSpritePaths[i], a_pigXPos[i], 300.0f, a_pigScales[i]))});
    }


    // === catapult ===
    std::unique_ptr<Catapult> catapult(new Catapult("../assets/Ang_Birds/Catapult.png", 100.0f, 480.0f, 0.4f));

    // Upcasting
    listDynamics(catapult.get(), "Catapult");


    //  === Non-interactables ===
    std::vector<std::unique_ptr<NonInteractable>> v_scenery;
    
    // Arrays for looping
    std::string a_scenerySpritePaths[4] = { "../assets/Ang_Birds/bush.png", "../assets/Ang_Birds/bush.png", "../assets/Ang_Birds/bush.png", "../assets/Ang_Birds/bush.png"};
    float a_sceneryXPos[4] = { 10.0f, 350.0f, 800.0f, 660.0f };

    for (int i = 0; i < 3; i++)
    {
        v_scenery.push_back(std::unique_ptr<NonInteractable>(new NonInteractable(a_scenerySpritePaths[i], a_sceneryXPos[i], 560.0f, 0.04f)));
    }

    ContactListener c;



    /*
    *       WINDOW SET UP
    */
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    //Box2D works in meters. SFML works in pixels.
    const float SCALE = 30.0f;

    //Can set a definition for PI.
    const float PI = 3.1415927;

    //setup world.
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);
    world.SetContactListener(&c);

    //Setup ground for the circle to move / bounce on.
    //Needs to have a body definition and a body. We use a raw pointer for the b2Body as Box2d does the management itself.
    //A body can be defined as having a position, velocity, and mass. 
    b2BodyDef b2_groundBodyDef;
    b2_groundBodyDef.position.Set(400.0f / SCALE, 590.0f / SCALE);
    b2Body* b2_groundBody = world.CreateBody(&b2_groundBodyDef);

    //Define a fixture shape that relates to the collision for the ground.
    b2PolygonShape b2_groundBox;
    b2_groundBox.SetAsBox(400.0f / SCALE, 10.0f / SCALE);
    b2_groundBody->CreateFixture(&b2_groundBox, 0.0f);

    //Set up the ground visualisation.
    sf::RectangleShape sf_groundVisual(sf::Vector2f(800.0f, 20.0f));
    sf_groundVisual.setOrigin(400.0f, 10.0f);
    sf_groundVisual.setFillColor(sf::Color(34, 139, 34)); // Forest Green

    //Setting up a wall for the ball to hit.
    b2BodyDef b2_wallDef;
    b2_wallDef.position.Set(750.0f / SCALE, 500.0f / SCALE);
    b2Body* b2_wallBody = world.CreateBody(&b2_wallDef);


    b2PolygonShape b2_wallBox;
    b2_wallBox.SetAsBox(10.0f / SCALE, 80.0f / SCALE);
    b2_wallBody->CreateFixture(&b2_wallBox, 0.0f);

    sf::RectangleShape sf_wallVisual(sf::Vector2f(20.0f, 160.0f));
    sf_wallVisual.setOrigin(10.0f, 80.0f);
    sf_wallVisual.setFillColor(sf::Color::Red);

    //Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    b2BodyDef b2_plankDef;

    b2_plankDef.type = b2_dynamicBody;
    b2_plankDef.position.Set(550.0f / SCALE, 450.0f / SCALE);
    b2Body* b2_plankBody = world.CreateBody(&b2_plankDef);

    b2PolygonShape b2_plankBox;
    b2_plankBox.SetAsBox(10.0f / SCALE, 60.0f / SCALE);

    b2FixtureDef b2_plankFixture;
    b2_plankFixture.shape = &b2_plankBox;
    b2_plankFixture.density = 1.5f;   // Light wood
    b2_plankFixture.friction = 0.3f;
    b2_plankBody->CreateFixture(&b2_plankFixture);

    sf::RectangleShape sf_plankVisual(sf::Vector2f(20.0f, 120.0f));
    sf_plankVisual.setOrigin(10.0f, 60.0f);
    sf_plankVisual.setFillColor(sf::Color(139, 69, 19)); // Brown

    //Create a ball that is fired when space is pressed. We need to first have a dynamic ball to do it.
    b2BodyDef b2_ballDef;
    b2_ballDef.type = b2_dynamicBody;
    b2_ballDef.position.Set(100.0f / SCALE, 500.0f / SCALE);
    b2Body* b2_ballBody = world.CreateBody(&b2_ballDef);

    b2CircleShape b2_circleShape;
    b2_circleShape.m_radius = 15.0f / SCALE;

    b2FixtureDef b2_ballFixture;
    b2_ballFixture.shape = &b2_circleShape;
    b2_ballFixture.density = 1.0f;
    b2_ballFixture.restitution = 0.5f; // Bounciness
    b2_ballBody->CreateFixture(&b2_ballFixture);

    sf::CircleShape sf_ballVisual(15.0f);
    sf_ballVisual.setOrigin(15.0f, 15.0f);
    sf_ballVisual.setFillColor(sf::Color::Yellow);




    /*
    *       BOX2D SET UP    
    */

    // === Birds ===
    float a_birdPhysX[3] = { 250.0f/SCALE, 300.0f / SCALE, 500.0f / SCALE };
    float a_birdPhysY[3] = { 560.0f/SCALE, 560.0f / SCALE, 560.0f / SCALE };
    uintptr_t a_birdID[3] = { 100, 100, 100 };

    auto birdSetupRange = mm_dynamicObjects.equal_range("Bird");
    int b_idx = 0;

    // Create all bird bodies from the range of birds in the multimap
    for (auto birdIt = birdSetupRange.first; birdIt != birdSetupRange.second; birdIt++)
    {
        birdIt->second->box2DSetup(world, a_birdPhysX[b_idx], a_birdPhysY[b_idx], 30.0f/SCALE, 1.0f, 0.3f, 0.5f, a_birdID[b_idx]);
        b_idx++;
    }


    // === Pigs ===
    float a_pigPhysX[3] = { 400.0f/SCALE, 600.0f / SCALE, 700.0f / SCALE };
    float a_pigPhysY[3] = { 300.0f/SCALE, 300.0f / SCALE, 300.0f / SCALE };
    uintptr_t a_pigID[3] = { 3, 4, 5 };

    auto pigIt = mm_dynamicObjects.equal_range("Pig");
    int p_idx = 0;

    // Create all pig bodies from the range of pigs in the multimap
    for (auto pigSetupRange = pigIt.first; pigSetupRange != pigIt.second; pigSetupRange++)
    {
        pigSetupRange->second->box2DSetup(world, a_pigPhysX[p_idx], a_pigPhysY[p_idx], 30.0f/SCALE, 1.0f, 0.3f, 0.5f, a_pigID[p_idx]);
        p_idx++;
    }


    // === Mouse input ===
    b2Body* a_birdBodies[3] = {nullptr, nullptr, nullptr}; // Array to move through to get bird

    auto birdBodyRange = mm_dynamicObjects.equal_range("Bird");
    int bodyIDx = 0;

    for (auto birdBodyIt = birdBodyRange.first; birdBodyIt != birdBodyRange.second; birdBodyIt++)
    {
        a_birdBodies[bodyIDx] = birdBodyIt->second->getBody();
        bodyIDx++;
    }

    int i_currentBird = 0; // Start at element 0 in array




    /*
    *       EVENTS
    */

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // INPUT HANDLING: Press SPACE to launch
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    // Reset position of the ball so that it can be fired again from its original poisition.
                    b2_ballBody->SetTransform(b2Vec2(100.0f / SCALE, 500.0f / SCALE), 0);
                    b2_ballBody->SetLinearVelocity(b2Vec2(0, 0));
                    b2_ballBody->SetAngularVelocity(0);

                    // Apply impulse (X-axis, Y-axis) Negative Y is UP in Box2D because gravity is positive.
                    b2_ballBody->ApplyLinearImpulse(b2Vec2(5.0f, -5.0f), b2_ballBody->GetWorldCenter(), true);

                    std::cout << "Firing!!!!" << std::endl;
                }
            }

            // Bird follows mouse cursor when mouse left click is pressed
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // Remove bird 1 after its launched and bird 2 has been clicked

                if (b_birdFired && mm_dynamicObjects.count("Bird") > 0)
                {
                    std::cout << "Entered loop" << std::endl;

                    // Destory box2D of the bird first
                    world.DestroyBody(a_birdBodies[i_currentBird]);
                    a_birdBodies[i_currentBird] = nullptr; // Can't access pointer 

                    // Destroy bird sprite second from multimap
                    // Current bird is the one at the front, so can just destroy first bird
                    auto it = mm_dynamicObjects.find("Bird");
                    mm_dynamicObjects.erase(it);
                    i_currentBird++;
                    b_birdFired = false;
                }
                if (mm_dynamicObjects.count("Bird") == 0)
                {
                    return 0;
                }

				b_isDragging = true; // Start dragging when left mouse button is pressed
                b2_dragStartPos = a_birdBodies[i_currentBird]->GetPosition();

                // Make body static
				a_birdBodies[i_currentBird]->SetType(b2_staticBody);
                a_birdBodies[i_currentBird]->SetLinearVelocity(b2Vec2(0, 0));
                a_birdBodies[i_currentBird]->SetAngularVelocity(0);
            }

            if (event.type == sf::Event::MouseMoved && b_isDragging)
            {
				b2Vec2 b2_mousePosIn(event.mouseMove.x / SCALE, event.mouseMove.y / SCALE); // Get mouse position
                a_birdBodies[i_currentBird]->SetTransform(b2_mousePosIn, 0); // Set  bird position to mouse position
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {

				// Stop dragging when left mouse button is released
				b_isDragging = false;
                a_birdBodies[i_currentBird]->SetType(b2_dynamicBody); // Return to dynamic object for collisions/physics when released

                // when button is released, calcuate impulse
				b2Vec2 b2_currentPos = a_birdBodies[i_currentBird]->GetPosition(); // Get current position of  bird

                // Slingshot vector (start - current)
                b2Vec2 b2_launchVec = b2_dragStartPos - b2_currentPos;
                
                // Impulse
                float f_speedMultiplier = 5.0f;
                b2Vec2 b2_impulseMagnitude(b2_launchVec.x * f_speedMultiplier, b2_launchVec.y * f_speedMultiplier);
                a_birdBodies[i_currentBird]->ApplyLinearImpulseToCenter(b2_impulseMagnitude, true);

                b_birdFired = true;
            }
        }




        /*
        *       UPDATE PHYSICS
        */

        // === Given objects ===
        world.Step(1.0f / 60.0f, 8, 3);

        //All of the visuals needs to be synced with the physics.

        sf_ballVisual.setPosition(b2_ballBody->GetPosition().x * SCALE, b2_ballBody->GetPosition().y * SCALE);
        sf_ballVisual.setRotation(b2_ballBody->GetAngle() * (180.0f / PI));

        //Static objects usually don't move, but we set the position once.
        sf_groundVisual.setPosition(b2_groundBody->GetPosition().x * SCALE, b2_groundBody->GetPosition().y * SCALE);
        sf_wallVisual.setPosition(b2_wallBody->GetPosition().x * SCALE, b2_wallBody->GetPosition().y * SCALE);

        // Dynamic wall.
        sf_plankVisual.setPosition(b2_plankBody->GetPosition().x * SCALE, b2_plankBody->GetPosition().y * SCALE);
        sf_plankVisual.setRotation(b2_plankBody->GetAngle() * (180.0f / PI));

      
        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue



        // === Added objects ===
        // Birds
        auto birdRange = mm_dynamicObjects.equal_range("Bird"); // Return 2 iterators -> first is first bird, second is one past last bird. Range of these iterators are all birds
        int i = i_currentBird; // Start at current bird

        // Iterator starts at first bird
        // Moves along until it reaches the second bound of the range (non-bird)
        for (auto it = birdRange.first; it != birdRange.second && i < 3; i++)
        {
            // Get the DynamicObject* pointer
            // If the DynamicObject* is a Bird*, make it into Bird*
            // If the DynamicObject* is a Pig*, make it nullptr
            
            // It points to an entry in multimap, { "Key", std::unique_putr<DynamicObject> }
            // it->second.get() to get the pointer
            Bird* bird = dynamic_cast<Bird*>(it->second.get());

            if (bird != nullptr) // if it is Bird*
            {
                bird->setPosition(a_birdBodies[i]->GetPosition().x * SCALE, a_birdBodies[i]->GetPosition().y * SCALE); // Set position
            }

            ++it;
        }



        // Pigs
        int i_pigIndex = 0;
        auto pigRange = mm_dynamicObjects.equal_range("Pig"); // Return 2 iterators -> first is first pig, second is one past last pig. Range of these iterators are all pigs

        // Iterator starts at first pig
        // Moves along until it reaches the second bound of the range (non-pig)
        for (auto it = pigRange.first; it != pigRange.second && i_pigIndex < 3; it++)
        {
            // Get the DynamicObject* pointer
            // If the DynamicObject* is a Pig*, make it into Pig*
            // If the DynamicObject* is a Bird*, make it nullptr

            // It points to an entry in multimap, { "Key", std::unique_putr<DynamicObject> }
            // it->second.get() to get the pointer
            Pig* pig = dynamic_cast<Pig*>(it->second.get());

            if (pig != nullptr) // if it is Pig*
            {
                pig->setPosition(it->second->getBody()->GetPosition().x * SCALE, it->second->getBody()->GetPosition().y * SCALE); // Set position
                i_pigIndex++;
            }

        }




        /*
        *       RENDERING
        */

        // === Scenery ===
        // Draw first so that its in the background
        for (auto& scenery : v_scenery) // Loop through all the scenery in the vector, not just the first one
        {
            scenery->render(window);
        }

        // === Given objects ===
        window.draw(sf_groundVisual);
        window.draw(sf_wallVisual);
        window.draw(sf_plankVisual);
        window.draw(sf_ballVisual);

        // === Added objects ===
		catapult->render(window);
        
        for (auto& obj : mm_dynamicObjects) // Loop through all the dynamic objects in the list, not just the first one
        {
            obj.second->render(window); // obj.second to render the object not the key
        }




        /*
        *       COLLISIONS
        */
        std::set<uintptr_t> s_collision = c.getPointer(); // Get the collision IDs from CollisionListener

        b2Body* a_pigBodies[3] = { nullptr, nullptr, nullptr }; // Remake a_pigBodies array
        auto pigCollisionRange = mm_dynamicObjects.equal_range("Pig"); // Get range of pigs from multimap
        int i_pColIdx = 0;

        // For every pig
        for (auto it = pigCollisionRange.first; it != pigCollisionRange.second; it++)
        {
            // Get the body from the unique pointer and store it in the a_pigBodies array
            a_pigBodies[i_pColIdx] = it->second->getBody();
            ++i_pColIdx;
        }

        for (int i = 0; i < 3; i++)
        {
            // s_collision.find to check pig ID was hit 
            if (a_pigBodies[i] != nullptr && s_collision.find(a_pigBodies[i]->GetUserData().pointer) != s_collision.end())
            {
                world.DestroyBody(a_pigBodies[i]); // Destroy that pigs body

                auto pigIt = mm_dynamicObjects.find("Pig");

                // Remove that sprite from multipmap
                if (pigIt != mm_dynamicObjects.end())
                {
                    mm_dynamicObjects.erase(pigIt);
                }
            }
        }

        c.clearPointers();

        window.display();
    }

    return 0;
}