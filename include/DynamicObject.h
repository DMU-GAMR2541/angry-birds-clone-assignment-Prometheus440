#pragma once
#include "GameObject.h"

class DynamicObject : public virtual GameObject{ // Virtual to stop ambiguity for UI inheritance
protected:
	//SFML variables
	sf::Sprite sp_rendered;
	sf::Texture sf_tex;

public:
	// Constructor
	DynamicObject(std::string texPath, float x, float y, float scale)
	{
		if (!sf_tex.loadFromFile(texPath)) // Load texture from file path, if fail then message
		{
			std::cout << "Failed to load dynamic object texture" << std::endl;
		}

		sp_rendered.setTexture(sf_tex); // Assign texture to the sprite
		sp_rendered.setPosition(x, y); // Set the position
		sp_rendered.setOrigin(sf_tex.getSize().x / 2.0f, sf_tex.getSize().y / 2.0f); // Align the texture to the centre of the instance
		sp_rendered.setScale(scale, scale); // Scale down the texture
	}

	// Default destructor
	~DynamicObject() override = default;



	// Override the pure virtual functions from GameObject
	void update() override
	{
		// Implementation for updating the dynamic object
	}
	void render(sf::RenderWindow& sf_window) override
	{
		// Implementation for rendering the dynamic object
	}

	// Pig bird and catapult all have new constructor and render
};