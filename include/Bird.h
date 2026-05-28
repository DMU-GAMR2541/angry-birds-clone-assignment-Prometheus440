#pragma once
#include "DynamicObject.h"

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
		}

		void update() override
		{

		}
};