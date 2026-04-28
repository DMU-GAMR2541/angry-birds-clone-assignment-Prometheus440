#pragma once

class GameObject {
	public:
	// Default constructor and destructor
	GameObject() = default;
	virtual ~GameObject() = default;

	// Pure virtual functions to be implemented by derived classes
	virtual void update() = 0;
	virtual void render() = 0;
};