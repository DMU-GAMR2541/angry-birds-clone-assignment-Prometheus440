#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
	public:
		sf::Sprite sp_rendered;
		sf::Texture sf_tex;
		std::string str_path;

	// Default constructor
	GameObject() = default;

	// Virtual destructor because polymorphism is being used
	virtual ~GameObject() = default;

	// Pure virtual functions to be implemented by derived classes
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& sf_window) = 0;

	virtual sf::Sprite getSprite()
	{
		return sp_rendered;
	}

	virtual std::string getSpritePath()
	{
		return str_path;
	}
};