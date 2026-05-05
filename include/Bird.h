#pragma once
#include "DynamicObject.h"

class Bird : public DynamicObject {
	private:
		float spawnX;
		float spawnY;
		float scale;

		//SFML variables
		sf::Sprite sp_rendered;
		sf::Texture sf_tex;


	public:

		//Constructor
		Bird(std::string texPath, float x, float y, float scaleFactor)
		{
			spawnX = x;
			spawnY = y;
			scale = scaleFactor;

			if (!sf_tex.loadFromFile(texPath)) // Load texture from file path, if fail then message
			{
				std::cout << "Failed to load pig texture" << endl;
			}

			sp_rendered.setTexture(sf_tex); // Assign texture to the sprite
			sp_rendered.setPosition(spawnX, spawnY); // Set the position
			sp_rendered.setOrigin(sf_tex.getSize().x / 2.0f, sf_tex.getSize().y / 2.0f); // Align the texture to the centre of the instance
			sp_rendered.setScale(scaleFactor, scaleFactor); // Scale down the bird texture
		}

		// Destructor
		~Bird() override
		{

		}

		void update() override
		{

		}

		void render(sf::RenderWindow& sf_window) override
		{
			sf_window.draw(sp_rendered);
		}

		void setPosition(float x, float y)
		{
			sp_rendered.setPosition(x, y);
		}
};