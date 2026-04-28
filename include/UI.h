#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"

class UI : public StaticObject, public DynamicObject {
	public:
	// Default constructor and destructor
	UI() = default;
	~UI() override = default;

	// Override the pure virtual functions from GameObject
	void update() override {
		// Implementation for updating the UI object
	}
	void render() override {
		// Implementation for rendering the UI object
	}
};