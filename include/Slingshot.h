#pragma once
#include <string>
#include <iostream>

using namespace std;

/// <summary>
/// A simple class that you can use to begin the testing process using Googletest.
/// </summary>
class Slingshot {
private:
    /// <summary>
    /// Variables that define the slingshot.
    /// </summary>
    int i_tension;
    std::string str_birdType;
    const int MAX_TENSION = 100;

public:
    Slingshot() : i_tension(0), str_birdType("Red") {}

    //Functions to test.
    void loadBird(std::string str_type) { str_birdType = str_type; }

    bool pullBack(int amount) {
        if (amount < 0) return false;
        i_tension = (i_tension + amount > MAX_TENSION) ? MAX_TENSION : i_tension + amount;
        return true;
    }

    int changeBirdType()
    {
        cout << "Enter bird type" << "\n";
        cin >> str_birdType;

        return 0;
    }

    int getTension() const { return i_tension; }
    std::string getBirdType() { return str_birdType; }

    void release() { i_tension = 0; }
};