#include <gtest/gtest.h>
#include <iostream>
#include "Enemy.h"
#include "Slingshot.h"
#include "bird.h"
#include "NonInteractable.h"

// Bird tests
class BirdTest : public testing::Test
{
public:
    std::unique_ptr<Bird> bird;
    std::unique_ptr<b2World> world;

    const float SCALE = 30.0f;

protected:
    void SetUp() override
    {
        bird = std::make_unique<Bird>("../assets/Ang_Birds/red.png", 250.0f, 300.0f, 0.025f);

        // Make 2D body for the movement test
        b2Vec2 gravity(0.0f, 9.8f);
        world = std::make_unique<b2World>(gravity);

        bird->box2DSetup(*world, 250.0f/SCALE, 300.0f/SCALE, 1.0f, 1.0f, 0.3f, 0.5f, 100);
    }
};

TEST_F(BirdTest, movementTest)
{
    // In main.cpp, birds position is updated using the bird bodies and matching the sprites to that location
    // Using sprite location will say if the body is working
    bird->setPosition(400.0f, 200.0f); // setPosition() moves sprite not body
    float f_x = bird->getSprite().getPosition().x;
    float f_y = bird->getSprite().getPosition().y;

    // Check correct setPosition() works 
    EXPECT_EQ(f_x, 400.0f);
    EXPECT_EQ(f_y, 200.0f);

    // Check physics engine is working
    b2Vec2 b2_impulse(5.0f, -10.0f);
    bird->getBody()->ApplyLinearImpulseToCenter(b2_impulse, true); // Apply an impulse to the bird body
    world->Step(1.0f/60.0f, 8, 3); // Advance all physics by one frame

    // Check body and sprite are both the same
    float f_bodyX = bird->getBody()->GetPosition().x * SCALE;
    float f_bodyY = bird->getBody()->GetPosition().y * SCALE;
    bird->setPosition(f_bodyX, f_bodyY); // Set the position of the sprite to the same as the body after impulse

    EXPECT_GT(bird->getSprite().getPosition().x, 250.0f);
}

TEST_F(BirdTest, tectureLoadTest)
{
    // If texture doesn't load, it's dimensions will be 0
    sf::Vector2 v_size = bird->getSprite().getTexture()->getSize();
    EXPECT_GT(v_size.x, 0);
    EXPECT_GT(v_size.y, 0);
}





// StaticObject tests
class StaticObjectTest : public testing::Test
{
public:
    std::unique_ptr<NonInteractable> bush;

    float f_windowWidth = 800.0f; // Window width from game window

protected:
    void SetUp() override
    {
        bush = std::make_unique<NonInteractable>("../assets/Ang_Birds/bush.png", 350.0f, 560.0f, 0.04f);
    }
};

TEST_F(StaticObjectTest, staticObjectPosition)
{
    // Fail first if the bush sprite is outside of the window bounds
    ASSERT_LT(bush->getSprite().getPosition().x, f_windowWidth);

    // Then test if sprite x position is at 350
    EXPECT_EQ(bush->getSprite().getPosition().x, 350.0f);
}