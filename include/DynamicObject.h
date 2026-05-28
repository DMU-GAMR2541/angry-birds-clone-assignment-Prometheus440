#pragma once
#include "GameObject.h"
#include "box2d/box2d.h"

extern std::string str_destructorLog; // extern so that all 3 classes that make up bird all point to the same string

class DynamicObject : public virtual GameObject { // Virtual to stop ambiguity for UI inheritance
protected:
	//SFML variables
	sf::Texture sf_tex;

	b2Body* b2_body;

public:
	// Shared constructor
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
	~DynamicObject() override
	{
		str_destructorLog += "DynamicObject"; // Add each name to check the order
	}

	// Override the pure virtual functions from GameObject
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

	void box2DSetup(b2World& world, float x, float y, float radius, float density, float friction, float restitution, uintptr_t id)
	{
		b2BodyDef b2_bodyDef; // Body definition (sets initial position and type)
		b2_bodyDef.type = b2_dynamicBody; // Set the body type to dynamic for physics simulation
		b2_bodyDef.position.Set(x, y);
		b2_body = world.CreateBody(&b2_bodyDef); // Create body in world

		b2CircleShape b2_circle; // Shape of object (geometry to define collision boundaries)
		b2_circle.m_radius = radius; // Set radius of the circle shape for the pig

		b2FixtureDef b2_bodyFixtureDef; // Fixture definition (attaches shape to body and adds friction, density and bounce)
		b2_bodyFixtureDef.shape = &b2_circle; // Set the shape of the fixture to the circle
		b2_bodyFixtureDef.density = 1.0f; // Set density
		b2_bodyFixtureDef.friction = 0.3f; // Set friction
		b2_bodyFixtureDef.restitution = 0.5f; // Set bounciness

		b2_body->GetUserData().pointer = id;
		b2_body->CreateFixture(&b2_bodyFixtureDef); // Attach fixture to body
	}

	b2Body* getBody()
	{
		return b2_body;
	}
};