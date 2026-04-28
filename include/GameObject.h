#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
	public:
	// Default constructor and destructor
	GameObject() = default;
	virtual ~GameObject() = default; // Virtual desctructor because polymorphism is being used

	// Pure virtual functions to be implemented by derived classes
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& sf_window) = 0;
};