#pragma once
#include "StaticObject.h"
#include <iostream>

class NonInteractable : public StaticObject {
private:
	sf::Sprite sp_rendered;
	sf::Texture sf_tex;

public:
	// Constructor and destructor
	NonInteractable(std::string texPath, float x, float y, float scaleFactor)
	{
		if (!sf_tex.loadFromFile(texPath)) // Load texture from file path, if fail then message
		{
			std::cout << "Failed to load non-interactable texture" << std::endl;
		}

		sp_rendered.setTexture(sf_tex); // Assign texture to the sprite
		sp_rendered.setPosition(x, y); // Set the position
		sp_rendered.setOrigin(sf_tex.getSize().x / 2.0f, sf_tex.getSize().y / 2.0f); // Align the texture to the centre of the instance
		sp_rendered.setScale(scaleFactor, scaleFactor); // Scale down the bird texture
	}

	// Default destructor
	~NonInteractable() override = default;

	// Override the pure virtual functions from GameObject
	void update() override {
		// Implementation for updating the non-interactable object
	}

	void render(sf::RenderWindow& window) override
	{
		window.draw(sp_rendered);
	}
};