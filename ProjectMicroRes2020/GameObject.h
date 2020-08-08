#pragma once

#include <Entropy/Math/Vec2.h>

#include <string>

#include "SpriteRenderer.h"
#include "Collider.h"

class GameObject
{
protected:
	BoxCollider collider; 
	std::string id;
	Entropy::Math::Vec2 position, velocity, texture_offset, sprite_index;
	std::string texture_name;

public:
	GameObject(std::string id, const char* spriteName, Entropy::Math::Vec2 spriteIndex = (0.0f, 0.0f),
		Entropy::Math::Vec2 position = Entropy::Math::Vec2(0.0f, 0.0f), Entropy::Math::Vec2 boxSize = Entropy::Math::Vec2(8.0f, 8.0f),
		Entropy::Math::Vec2 boxOffset = Entropy::Math::Vec2(4.0f, 4.0f), Entropy::Math::Vec2 textureOffset = Entropy::Math::Vec2(0.0f, 0.0f)) :
		id(id), texture_name(spriteName), sprite_index(spriteIndex), position(position), velocity(0.0f, 0.0f),
		collider(position, boxSize, boxOffset), texture_offset(textureOffset) {};
	GameObject() {};

	virtual void Draw(SpriteRenderer& renderer);

	virtual void Update();
	virtual void undoUpdate();

	void setVelocity(Entropy::Math::Vec2 velocity);
	void setVelocityX(float velocity);
	void setVelocityY(float velocity);

	Entropy::Math::Vec2 getVelocity();
	float getVelocityX();
	float getVelocityY();

	void setPosition(Entropy::Math::Vec2 position);

	void setSpriteIndex(Entropy::Math::Vec2 spriteIndex);
	void setSpriteIndexX(float x);
	void setSpriteIndexY(float y);

	std::string getID();

	BoxCollider& getCollider();

	bool detectCollion(GameObject& other);
	bool detectCollion(BoxCollider& other);
};