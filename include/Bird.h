#pragma once
#include "DynamicObject.h"

class Bird : public DynamicObject {
	private:
		float spawnX;
		float spawnY;
		float scale;


		b2Body* b2_body; // Box2D body for physics simulation


	public:
		//Constructor
		Bird(std::string texPath, float x, float y, float scaleFactor)
		{

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