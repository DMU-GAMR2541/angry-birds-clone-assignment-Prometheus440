#pragma once
#include "DynamicObject.h"

class Pig : public DynamicObject {
	private:
		int health;
		bool popped;

	public:
		// Constructor
		Pig(int hp) {
			health = hp;
			popped = false;
		}
};