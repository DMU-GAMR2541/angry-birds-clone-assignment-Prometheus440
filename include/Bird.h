#pragma once
#include "DynamicObject.h"

extern std::string str_destructorLog; // extern so that all 3 classes that make up bird all point to the same string

class Bird : public DynamicObject {
	private:
		b2Body* b2_body; // Box2D body for physics simulation


	public:
		//Constructor
		Bird(std::string texPath, float x, float y, float scale) : DynamicObject(texPath, x, y, scale)
		{

		}

		// Destructor
		~Bird() override
		{
			str_destructorLog += "Bird"; // Add each name to check the order
		}

		void update() override
		{

		}
};