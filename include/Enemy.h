#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Enemy {
    /// <summary>
    /// Varaibles that define an enemy.
    /// </summary>
private:
    int i_health;
    bool b_isDestroyed;
    float x;
    float y;

public:
    //Default constructor for an enemy. 
    Enemy() = default;
    Enemy(int i_initialHealth, float xPos = 0, float yPos = 0) : i_health(i_initialHealth), b_isDestroyed(false), x(xPos), y(yPos) {}

    //Class functions to be tested.
    void takeDamage(int damage) {
        if (damage < 0) return;
        i_health -= damage;
        if (i_health <= 0) {
            i_health = 0;
            b_isDestroyed = true;
        }
    }

    vector<float> locateEnemy() const
    {
        return { x, y };
    }

    void setHealth()
    {
        cout << "Enter health value" << "\n";
        cin >> i_health;
    }

    int getHealth() const { return i_health; }
    bool checkIfPopped() const { return b_isDestroyed; }
};