#pragma once
#include "GameObject.h"

class StaticObject : public virtual GameObject { // Virtual to stop ambiguity for UI inheritance
	public:
	// Default constructor and destructor
	StaticObject() = default;
	~StaticObject() override = default;

	// Override the pure virtual functions from GameObject
	void update() override {
		// Implementation for updating the static object
	}
	void render() override {
		// Implementation for rendering the static object
	}
};