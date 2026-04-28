#pragma once
#include "StaticObject.h"

class NonInteractable : public StaticObject {
public:
	// Default constructor and destructor
	NonInteractable() = default;
	~NonInteractable() override = default;

	// Override the pure virtual functions from GameObject
	void update() override {
		// Implementation for updating the non-interactable object
	}
	void render() override {
		// Implementation for rendering the non-interactable object
	}
};