#pragma once
#include "DynamicObject.h"

class Pig : public DynamicObject {
	private:
		int i_health;
		bool b_popped;

	public:
		// Constructor
		Pig(int hp, std::string texPath, float x, float y, float scale) : DynamicObject(texPath, x, y, scale)
		{
			i_health = hp;
			b_popped = false;
		}

		// Destructor
		~Pig() override
		{

		}

		void update() override
		{

		}
};