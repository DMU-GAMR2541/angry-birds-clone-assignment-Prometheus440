#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <list>

#include "Pig.h"
#include "Bird.h"
#include "Catapult.h"
#include "NonInteractable.h"

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

    // === Pointer variables ===
    std::unique_ptr<Pig> pig1(new Pig(3, "../assets/Ang_Birds/pig.png", 400.0f, 300.0f, 0.04f));
    std::unique_ptr<Pig> pig2(new Pig(3, "../assets/Ang_Birds/pig_helmet.png", 600.0f, 350.0f, 0.225f));
    std::unique_ptr<Catapult> catapult(new Catapult("../assets/Ang_Birds/Catapult.png", 400.0f, 480.0f, 0.4f));

    // Upcasting
    listDynamics(pig1.get(), "Pig");
    listDynamics(catapult.get(), "Catapult");

    // === Birds ===
    std::list<std::unique_ptr<Bird>> ls_birds; // Make a list of the unique bird pointers

    // Arrays for looping
    std::string a_birdSpritePaths[3] = { "../assets/Ang_Birds/red.png", "../assets/Ang_Birds/yellow.png", "../assets/Ang_Birds/blue.png"};
    float a_birdXPos[3] = {250.0f, 300.0f, 500.0f};
    float a_birdScales[3] = {0.025f, 0.075f, 0.065f};
    
    for (int i = 0; i < 3; i++)
    {
        ls_birds.push_back(std::unique_ptr<Bird>(new Bird(a_birdSpritePaths[i], a_birdXPos[i], 550.0f, a_birdScales[i])));
    }

    //  === Non-interactables ===
    std::vector<std::unique_ptr<NonInteractable>> v_scenery;
    
    // Arrays for looping
    std::string a_scenerySpritePaths[4] = { "../assets/Ang_Birds/bush.png", "../assets/Ang_Birds/bush.png", "../assets/Ang_Birds/bush.png", "../assets/Ang_Birds/bush.png"};
    float a_sceneryXPos[4] = { 10.0f, 350.0f, 800.0f, 660.0f };

    for (int i = 0; i < 3; i++)
    {
        v_scenery.push_back(std::unique_ptr<NonInteractable>(new NonInteractable(a_scenerySpritePaths[i], a_sceneryXPos[i], 560.0f, 0.04f)));
    }




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

    // === pig1 ===
    b2Vec2 b2_pig1PosIn(400.0f / SCALE, 300.0f / SCALE); // Convert from pixels to meters for Box2D

    b2Vec2 b2_pig1Pos; // position in game world
    b2BodyDef b2_pig1Def; // Body definition (sets initial position and type)
    b2FixtureDef b2_pig1FixtureDef; // Fixture definition (attaches shape to body and adds friction, density and bounce)
    b2Body* b2_pig1Body; // Body (physical instance in world)
    b2CircleShape b2_pig1Circle; // Shape of object (geometry to define collision boundaries)
	b2_pig1Circle.m_radius = 30.0f / SCALE; // Set radius of the circle shape for the pig

    b2_pig1Def.type = b2_dynamicBody; // Set the body type to dynamic for physics simulation
    b2_pig1Def.position = b2_pig1PosIn;
    b2_pig1Body = world.CreateBody(&b2_pig1Def); // Create body in world

    // Set up fixture
    b2_pig1FixtureDef.shape = &b2_pig1Circle; // Set the shape of the fixture to the circle
    b2_pig1FixtureDef.density = 1.0f; // Set density
    b2_pig1FixtureDef.friction = 0.3f; // Set friction
    b2_pig1FixtureDef.restitution = 0.5f; // Set bounciness

    b2_pig1Body->CreateFixture(&b2_pig1FixtureDef); // Attach fixture to body


    // === pig2 ===
    b2Vec2 b2_pig2PosIn(400.0f / SCALE, 300.0f / SCALE); // Convert from pixels to meters for Box2D

    b2Vec2 b2_pig2Pos; // position in game world
    b2BodyDef b2_pig2Def; // Body definition (sets initial position and type)
    b2FixtureDef b2_pig2FixtureDef; // Fixture definition (attaches shape to body and adds friction, density and bounce)
    b2Body* b2_pig2Body; // Body (physical instance in world)
    b2CircleShape b2_pig2Circle; // Shape of object (geometry to define collision boundaries)
    b2_pig2Circle.m_radius = 30.0f / SCALE; // Set radius of the circle shape for the pig

    b2_pig2Def.type = b2_dynamicBody; // Set the body type to dynamic for physics simulation
    b2_pig2Def.position = b2_pig2PosIn;
    b2_pig2Body = world.CreateBody(&b2_pig2Def); // Create body in world

    // Set up fixture
    b2_pig2FixtureDef.shape = &b2_pig2Circle; // Set the shape of the fixture to the circle
    b2_pig2FixtureDef.density = 1.0f; // Set density
    b2_pig2FixtureDef.friction = 0.3f; // Set friction
    b2_pig2FixtureDef.restitution = 0.5f; // Set bounciness

    b2_pig2Body->CreateFixture(&b2_pig2FixtureDef); // Attach fixture to body


    // === red bird ===
    b2Vec2 b2_redBirdPosIn(250.0f / SCALE, 560.0f / SCALE); // Convert from pixels to meters for Box2D

    b2Vec2 b2_redBirdPos; // position in game world
    b2BodyDef b2_redBirdDef; // Body definition (sets initial position and type)
    b2FixtureDef b2_redBirdFixtureDef; // Fixture definition (attaches shape to body and adds friction, density and bounce)
    b2Body* b2_redBirdBody; // Body (physical instance in world)
    b2CircleShape b2_redBirdCircle; // Shape of object (geometry to define collision boundaries)
    b2_redBirdCircle.m_radius = 30.0f / SCALE; // Set radius of the circle shape for the pig

    b2_redBirdDef.type = b2_dynamicBody; // Set the body type to dynamic for physics simulation
    b2_redBirdDef.position = b2_redBirdPosIn;
    b2_redBirdBody = world.CreateBody(&b2_redBirdDef); // Create body in world

    // Set up fixture
    b2_redBirdFixtureDef.shape = &b2_redBirdCircle; // Set the shape of the fixture to the circle
    b2_redBirdFixtureDef.density = 1.0f; // Set density
    b2_redBirdFixtureDef.friction = 0.3f; // Set friction
    b2_redBirdFixtureDef.restitution = 0.5f; // Set bounciness

    b2_redBirdBody->CreateFixture(&b2_redBirdFixtureDef); // Attach fixture to body


    // === yellow bird ===
    b2Vec2 b2_yellowBirdPosIn(300.0f / SCALE, 560.0f / SCALE); // Convert from pixels to meters for Box2D
	b2Vec2 b2_yellowStartPosition = b2_yellowBirdPosIn; // Store the starting position for impulse calculation when released

    b2Vec2 b2_yellowBirdPos; // position in game world
    b2BodyDef b2_yellowBirdDef; // Body definition (sets initial position and type)
    b2FixtureDef b2_yellowBirdFixtureDef; // Fixture definition (attaches shape to body and adds friction, density and bounce)
    b2Body* b2_yellowBirdBody; // Body (physical instance in world)
    b2CircleShape b2_yellowBirdCircle; // Shape of object (geometry to define collision boundaries)
    b2_yellowBirdCircle.m_radius = 30.0f / SCALE; // Set radius of the circle shape for the pig

    b2_yellowBirdDef.type = b2_dynamicBody; // Set the body type to dynamic for physics simulation
    b2_yellowBirdDef.position = b2_yellowBirdPosIn;
    b2_yellowBirdBody = world.CreateBody(&b2_yellowBirdDef); // Create body in world

    // Set up fixture
    b2_yellowBirdFixtureDef.shape = &b2_yellowBirdCircle; // Set the shape of the fixture to the circle
    b2_yellowBirdFixtureDef.density = 1.0f; // Set density
    b2_yellowBirdFixtureDef.friction = 0.3f; // Set friction
    b2_yellowBirdFixtureDef.restitution = 0.5f; // Set bounciness

    b2_yellowBirdBody->CreateFixture(&b2_yellowBirdFixtureDef); // Attach fixture to body


    // === blue bird ===
    b2Vec2 b2_blueBirdPosIn(500.0f / SCALE, 560.0f / SCALE); // Convert from pixels to meters for Box2D
    b2Vec2 b2_blueStartPosition = b2_blueBirdPosIn; // Store the starting position for impulse calculation when released

    b2Vec2 b2_blueBirdPos; // position in game world
    b2BodyDef b2_blueBirdDef; // Body definition (sets initial position and type)
    b2FixtureDef b2_blueBirdFixtureDef; // Fixture definition (attaches shape to body and adds friction, density and bounce)
    b2Body* b2_blueBirdBody; // Body (physical instance in world)
    b2CircleShape b2_blueBirdCircle; // Shape of object (geometry to define collision boundaries)
    b2_blueBirdCircle.m_radius = 30.0f / SCALE; // Set radius of the circle shape for the pig

    b2_blueBirdDef.type = b2_dynamicBody; // Set the body type to dynamic for physics simulation
    b2_blueBirdDef.position = b2_blueBirdPosIn;
    b2_blueBirdBody = world.CreateBody(&b2_blueBirdDef); // Create body in world

    // Set up fixture
    b2_blueBirdFixtureDef.shape = &b2_blueBirdCircle; // Set the shape of the fixture to the circle
    b2_blueBirdFixtureDef.density = 1.0f; // Set density
    b2_blueBirdFixtureDef.friction = 0.3f; // Set friction
    b2_blueBirdFixtureDef.restitution = 0.5f; // Set bounciness

    b2_blueBirdBody->CreateFixture(&b2_blueBirdFixtureDef); // Attach fixture to body




    /*
    *       EVENTS
    */
    // For mouse input
    b2Body* a_birdBodies[3] = {b2_redBirdBody, b2_yellowBirdBody, b2_blueBirdBody}; // Array to move through to get bird
    int i_currentBird = 0; // Start at element 0 in array

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

            // Added for impulse example when E is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::E)
                {
                    // Calculate launch vector (target pos - origin pos)
                    b2Vec2 b2_originPos = b2_redBirdBody->GetPosition();
                    b2Vec2 b2_targetPos = b2_pig1Body->GetPosition(); // Target is pig1

                    b2Vec2 b2_launchVec; // Making launch direction
                    b2_launchVec.x = b2_targetPos.x - b2_originPos.x;
                    b2_launchVec.y = b2_targetPos.y - b2_originPos.y;

                    // Impulse
                    float f_speedMultiplier = 3.0f;
                    b2Vec2 b2_impulseMagnitude(b2_launchVec.x * f_speedMultiplier, b2_launchVec.y * f_speedMultiplier);
                    b2_redBirdBody->ApplyLinearImpulseToCenter(b2_impulseMagnitude, true);
                }
            }

            // Bird follows mouse cursor when mouse left click is pressed
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // Remove bird 1 after its launched and bird 2 has been clicked

                if (b_birdFired && !ls_birds.empty())
                {
                    std::cout << "Entered loop" << std::endl;
                    // Destory box2D of the bird first
                    world.DestroyBody(a_birdBodies[i_currentBird]);
                    a_birdBodies[i_currentBird] = nullptr; // Can't access pointer 

                    // Destroy bird sprite
                    ls_birds.pop_front();
                    i_currentBird++;
                    b_birdFired = false;
                }
                if (ls_birds.empty())
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
        // Pigs 
        pig1->setPosition(b2_pig1Body->GetPosition().x * SCALE, b2_pig1Body->GetPosition().y * SCALE);
        pig2->setPosition(b2_pig2Body->GetPosition().x * SCALE, b2_pig2Body->GetPosition().y * SCALE);

        // Birds
        auto it = ls_birds.begin(); // iterator to move through bird list, starting at first bird
        for (int i = i_currentBird; i < 3 && it != ls_birds.end(); i++) // Start at current bird as they are removed when fired, and make sure list is not empty
        {
            (*it)->setPosition(a_birdBodies[i]->GetPosition().x* SCALE, a_birdBodies[i]->GetPosition().y* SCALE); // Set pos of bird
            ++it; // Move iterator
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
        pig1->render(window);
        pig2->render(window);
        
        for (auto& bird : ls_birds) // Loop through all the birds in the list, not just the first one
        {
            bird -> render(window);
        }

        window.display();
    }

    return 0;
}