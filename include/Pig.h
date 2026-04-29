#pragma once
#include "DynamicObject.h"

class Pig : public DynamicObject {
	private:
		int health;
		bool popped;
		float spawnX;
		float spawnY;
		float scaleFactor; // Scale factor for the pig texture

		// SFML variables
		sf::Sprite sp_rendered;
		sf::Texture sf_tex;

	public:
		// Constructor
		Pig(int hp, std::string texPath, float x, float y, float scale)
		{
			health = hp;
			popped = false;
			spawnX = x;
			spawnY = y;
			scaleFactor = scale;

			if (!sf_tex.loadFromFile(texPath))
			{
				std::cout << "Failed to load pig texture" << std::endl;
			}

			sp_rendered.setTexture(sf_tex); // Assign texture to the sprite
			sp_rendered.setPosition(spawnX, spawnY); // Set the position
			sp_rendered.setOrigin(sf_tex.getSize().x / 2.0f, sf_tex.getSize().y / 2.0f); // Align the texture to the centre of the instance
			sp_rendered.setScale(scaleFactor, scaleFactor); // Scale down the pig texture
		}

		// Destructor
		~Pig() override
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