#pragma once
#include "DynamicObject.h"

class Pig : public DynamicObject {
	private:
		int health;
		bool popped;

		//SFML variables
		sf::Sprite sp_rendered;
		sf::Texture sf_tex;

	public:
		// Constructor
		Pig(int hp, std::string texPath)
		{
			health = hp;
			popped = false;

			if (!sf_tex.loadFromFile(texPath)) // Load texture from file path, if fail then message
			{
				std::cout << "Failed to load pig texture" << endl;
			}

			sp_rendered.setTexture(sf_tex); // Assign texture to the sprite
			sp_rendered.setOrigin(sf_tex.getSize().x / 2.0f, sf_tex.getSize().y / 2.0f); // Align the texture to the centre of the instance
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