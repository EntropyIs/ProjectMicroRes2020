#pragma once

#include <Entropy/Math/Vec2.h>

#include <string>

#include "SpriteRenderer.h"

class GameObject
{
public:
	std::string name;
	Entropy::Math::Vec2 position, velocity, box_size, box_offset, texture_offset, sprite_index;
	std::string texture_name;

	GameObject() {};

public:
	GameObject(const char* name, const char* spriteName, Entropy::Math::Vec2 spriteIndex = (0.0f, 0.0f),
		Entropy::Math::Vec2 position = Entropy::Math::Vec2(0.0f, 0.0f), Entropy::Math::Vec2 boxSize = Entropy::Math::Vec2(8.0f, 8.0f),
		Entropy::Math::Vec2 boxOffset = Entropy::Math::Vec2(4.0f, 4.0f), Entropy::Math::Vec2 textureOffset = Entropy::Math::Vec2(0.0f, 0.0f)) :
		name(name), texture_name(spriteName), sprite_index(spriteIndex), position(position), velocity(0.0f, 0.0f),
		box_size(boxSize), box_offset(boxOffset), texture_offset(textureOffset) {};

	virtual void Draw(SpriteRenderer& renderer);

	virtual void Update();

	void setVelocity(Entropy::Math::Vec2 velocity);
	void setVelocityX(float velocity);
	void setVelocityY(float velocity);

	bool detectCollions(GameObject& other);
};