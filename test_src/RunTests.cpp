#include <gtest/gtest.h>
#include "Enemy.h"
#include "Slingshot.h"
#include "bird.h"
#include "NonInteractable.h"

/// <summary>
///Taken from the GoogleTest primer. 
/// </summary>

// The fixture for testing class Foo.
class EnemyTest : public testing::Test {
public:
    std::unique_ptr<Enemy> enemy;
    std::unique_ptr<Slingshot> slingshot;

protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    EnemyTest() {
        // You can do set-up work for each test here.

    }

    ~EnemyTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        enemy = std::make_unique<Enemy>(50); // All enemnies in this test suite start with 50 HP.            
        slingshot = std::make_unique<Slingshot>(); // New slingshot for this test suite.
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

};

// Bird tests
class BirdTest : public testing::Test
{
public:
    std::unique_ptr<Bird> bird;

protected:
    void SetUp() override
    {
        bird = std::make_unique<Bird>("../assets/Ang_Birds/red.png", 250.0f, 300.0f, 0.025f);
    }
};

TEST_F(BirdTest, spriteLocationTest)
{
    float f_x = bird->getSprite().getPosition().x;
    EXPECT_EQ(f_x, 250.0f);
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







//A single test, not a fixture. No setup is called.
TEST(Enemy, First_test) {
    Enemy e(100);
    EXPECT_GT(e.getHealth(), 99);
    SUCCEED() << "Test test passed";
    FAIL() << "Test didn't pass";
}

//TEST_F(EnemyTest, LethalDamagePopsPig) {
//    enemy->takeDamage(60);
//    EXPECT_TRUE(enemy->checkIfPopped());
//}
//
//TEST_F(EnemyTest, EnemyPosition) {
//    Enemy e(50, 10.0f, 13.0f);
//    vector<float> pos = e.locateEnemy();
//
//    EXPECT_EQ(pos[0], 10.0f);
//    EXPECT_EQ(pos[1], 14.0f);
//
//    FAIL() << "Enemy is lost";
//    SUCCEED() << "Enemy is found";
//}
//
//TEST_F(EnemyTest, BirdTypeCheck)
//{
//    std::string str = "red";
//    const char* c = str.c_str();
//    ASSERT_STRCASEEQ("red", c);
//    EXPECT_STRNE("red", c);
//    EXPECT_STREQ("pink", c);
//}
//
//TEST_F(EnemyTest, BirdTypeEnter)
//{
//    slingshot->changeBirdType();
//    std::string str = "Green";
//    const char* c = str.c_str();
//    EXPECT_STRCASEEQ("Green", c);
//    SUCCEED() << "Enemy type is now green";
//}
//
//TEST_F(EnemyTest, EnemyHealthEnter)
//{
//    int i_prevHealth = enemy->getHealth();
//    enemy->setHealth();
//    EXPECT_TRUE(i_prevHealth < enemy->getHealth());
//    FAIL() << "Enemy has taken damage";
//    SUCCEED() << "Enemy has healed";
//
//}

// Parameterised tests
class ParamTest : public::testing::TestWithParam<int> {
protected:
    ParamTest() = default;
    ~ParamTest() = default;

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).

    }

    void TearDown() override
    {

    }
};

TEST_P(ParamTest, SimpleTest)
{
    int i_test = GetParam();
    std::cout << "Param value:: " << i_test << std::endl;
    EXPECT_GT(i_test, 1);
}

INSTANTIATE_TEST_SUITE_P( Simple,ParamTest, ::testing::Values(1, 2, 3, 4, 5));

// Test
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}