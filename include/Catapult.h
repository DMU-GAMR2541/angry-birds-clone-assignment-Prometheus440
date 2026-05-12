#pragma once
#include "DynamicObject.h"

class Catapult : public DynamicObject{
public:
	//Constructor
	Catapult(std::string texPath, float x, float y, float scale) : DynamicObject(texPath, x, y, scale)
	{

	}

	// Destructor
	~Catapult() override
	{

	}

	void update() override
	{

	}
};