#pragma once
#include "DynamicObject.h"

class Catapult : public DynamicObject {
	private:
		// SFML variables
		sf::Sprite sp_rendered;
		sf::Texture sf_tex;
		
		float spawnX;
		float spawnY;
		float scaleFactor; // Scale factor for the pig texture


	public:
		// Constructor
		Catapult(std::string texPath, float x, float y, float scale)
		{
			spawnX = x;
			spawnY = y;
			scaleFactor = scale;

			if (!sf_tex.loadFromFile(texPath))
			{
				std::cout << "Failed to load catapult texture" << std::endl;
			}

			sp_rendered.setTexture(sf_tex); // Assign texture to the sprite
			sp_rendered.setPosition(spawnX, spawnY); // Set the position
			sp_rendered.setOrigin(sf_tex.getSize().x / 2.0f, sf_tex.getSize().y / 2.0f); // Align the texture to the centre of the instance
			sp_rendered.setScale(scaleFactor, scaleFactor); // Scale down the pig texture
		}

		// Destructor
		~Catapult() override
		{

		}

		void update() override
		{

		}

		void render(sf::RenderWindow& sf_window) override
		{
			sf_window.draw(sp_rendered);
		}
};