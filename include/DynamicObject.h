#pragma once
#include "GameObject.h"

class DynamicObject : public GameObject {
	public:
	// Default constructor and destructor
	DynamicObject() = default;
	~DynamicObject() override = default;

	// Override the pure virtual functions from GameObject
	void update() override {
		// Implementation for updating the dynamic object
	}
	void render() override {
		// Implementation for rendering the dynamic object
	}
};