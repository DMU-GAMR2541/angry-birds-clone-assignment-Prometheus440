#include <gtest/gtest.h>
#include "Enemy.h"
#include "Slingshot.h"

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

//A single test, not a fixture. No setup is called.
TEST(Enemy, First_test) {
    Enemy e(100);
    EXPECT_GT(e.getHealth(), 99);
    SUCCEED() << "Test test passed";
    FAIL() << "Test didn't pass";
}

TEST_F(EnemyTest, LethalDamagePopsPig) {
    enemy->takeDamage(60);
    EXPECT_TRUE(enemy->checkIfPopped());
}

TEST_F(EnemyTest, EnemyPosition) {
    Enemy e(50, 10.0f, 13.0f);
    vector<float> pos = e.locateEnemy();

    EXPECT_EQ(pos[0], 10.0f);
    EXPECT_EQ(pos[1], 14.0f);

    FAIL() << "Enemy is lost";
    SUCCEED() << "Enemy is found";
}

TEST_F(EnemyTest, BirdTypeCheck)
{
    std::string str = "red";
    const char* c = str.c_str();
    ASSERT_STRCASEEQ("red", c);
    EXPECT_STRNE("red", c);
    EXPECT_STREQ("pink", c);
}

TEST_F(EnemyTest, BirdTypeEnter)
{
    slingshot->changeBirdType();
    std::string str = "Green";
    const char* c = str.c_str();
    EXPECT_STRCASEEQ("Green", c);
    SUCCEED() << "Enemy type is now green";
}

TEST_F(EnemyTest, EnemyHealthEnter)
{
    int i_prevHealth = enemy->getHealth();
    enemy->setHealth();
    EXPECT_TRUE(i_prevHealth < enemy->getHealth());
    FAIL() << "Enemy has taken damage";
    SUCCEED() << "Enemy has healed";

}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}