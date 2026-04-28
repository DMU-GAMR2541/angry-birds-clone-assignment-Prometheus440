#pragma once
#include "DynamicObject.h"

class Catapult : public DynamicObject {
	private:
		int tension;
		bool loaded;

	public:
		// Constructor
		Catapult() {
			tension = 0;
			loaded = false;
		}
};