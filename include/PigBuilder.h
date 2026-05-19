#pragma once

#include "Pig.h"
#include <string>
#include <iostream>
#include "box2d/box2d.h"

class PigBuilder
{
private:
	std::string str_spritePath = "";
	float f_x = 0.0f;
	float f_y = 0.0f;
	float f_scale = 0.1f;

	int i_health = 1;

	float f_density = 1.0f;
	float f_friction = 0.3f;
	float f_restitution = 0.5f;
	float f_radius = 1.0f;

	b2World* b2_world = nullptr;

public:
	PigBuilder& setSprite(std::string path, float scale)
	{
		str_spritePath = path;
		f_scale = scale;
		return *this;
	}

	PigBuilder& setPosition(float x, float y)
	{
		f_x = x;
		f_y = y;
		return *this;
	}

	PigBuilder& setHealth(int health)
	{
		i_health = health;
		return *this;
	}

	PigBuilder& setWorld(b2World* world)
	{
		b2_world = world;
		return *this;
	}

	PigBuilder& setFixture(float density, float friction, float restitution, float radius)
	{
		f_density = density;
		f_friction = friction;
		f_restitution = restitution;
		f_radius = radius;
		return *this;
	}

	Pig* build()
	{
		std::cout << "=== Building pig ===" << std::endl;
		std::cout << "Sprite: " << str_spritePath << std::endl;
		std::cout << "Position: (" << f_x << ", " << f_y << ")" << std::endl;
		std::cout << "Scale: " << f_scale << std::endl;
		std::cout << "Health: " << i_health << std::endl;
		std::cout << "Density: " << f_density << std::endl;
		std::cout << "Friction: " << f_friction << std::endl;
		std::cout << "Restitution: " << f_restitution << std::endl;
		std::cout << "====================" << std::endl;

		return new Pig(i_health, str_spritePath, f_x, f_y, f_scale);
	}
};