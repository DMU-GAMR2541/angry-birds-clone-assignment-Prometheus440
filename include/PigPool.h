#pragma once
#include "Pig.h"
#include <queue>
#include <vector>

class PigPool
{
private:
	std::vector<std::unique_ptr<Pig>> v_allPigs; // Owns all pigs
	std::queue<Pig*> q_available; // List of inactive pigs

public:
	PigPool(int size)
	{
		for (int i = 0; i < size; i++) // Create a pool where number of pigs = size
		{
			std::unique_ptr<Pig> pig(new Pig(1, "../assets/Ang_Birds/pig.png", 400.0f, 300.0f, 0.04f)); // Create a new pig and make it a unique pointer
			q_available.push(pig.get()); // Get pointer of pig and add it to list of inactive pigs for getPig()
			v_allPigs.push_back(std::move(pig)); // Move pig to the big list (v_allPigs) and have queue reference it
		}
	}

	Pig* getPig()
	{
		if (q_available.empty())
		{
			return nullptr; // Stop crashes is no available pigs
		}

		Pig* pig = q_available.front(); // Get first inactice pig from queue 
		q_available.pop(); // Remove it because it becomes active

		return pig; // Return pointer of first inactive pig to be used in-game
	}

	void releasePig(Pig* pig)
	{
		q_available.push(pig); // Stick dead pig at the end of the inactive queue to be respawned
	}
};